#pragma once
#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"Shader.h"
#include"glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Mesh.h"
#include "Model.h"
#include "Animator.h"
#include "Model_Animation.h"

class FTRenderer {
public:
	void CreateGLFWWindow(int width, int height);
private:
	void processInput(GLFWwindow* window);
};