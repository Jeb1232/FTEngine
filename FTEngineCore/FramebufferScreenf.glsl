#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform float exposureValue = 1.0f;
uniform float contrastValue = 1.0f;


uniform sampler2D depthMap;
uniform float near_plane = 0.1f;
uniform float far_plane = 100.0f;
uniform float density;
uniform vec3 fogColor;
uniform bool fogEnabled;
uniform bool toneMappingEnabled;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));		
}

void main()
{
    float depthValue = LinearizeDepth(texture(depthMap, TexCoords).r) * far_plane;
    float fogFactor = (density / sqrt(log(2))) * max(0.0f, depthValue - 0.0f);
    fogFactor = exp2(-fogFactor * fogFactor);
    vec3 col = texture(screenTexture, TexCoords).rgb * exposureValue;
    vec3 aces = (col*(2.51f*col+0.03f))/(col*(2.43f*col+0.59f)+0.14f);
    col = contrastValue * (col - 0.5f) + 0.5f;
    vec3 fogOutput = mix(fogColor, col, fogFactor);
    if(fogEnabled)
    {
        if(toneMappingEnabled)
        {
            FragColor = vec4(mix(fogColor, aces, fogFactor), 1.0);
        }
        else
        {
            FragColor = vec4(mix(fogColor, col, fogFactor), 1.0);
        }
    }
    else
    {
        if(toneMappingEnabled)
        {
            FragColor = vec4(aces, 1.0);
        }
        else
        {
            FragColor = vec4(col, 1.0);
        }
    }
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
} 