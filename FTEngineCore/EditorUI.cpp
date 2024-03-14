#include"EditorUI.h"
#include<iostream>

void ShowDockingDisabledMessage();


void FTEditorUI::InitUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void FTEditorUI::NewImGuiFrame() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}



void FTEditorUI::UIMainLoop() 
{
    bool dock = true;
    FTEditorUI::ShowExampleAppDockSpace(&dock);
    



	ImGui::Begin("Properties");
    {
        ImGui::InputFloat3("Position", pos);
        ImGui::InputFloat3("Rotation", rot);
        ImGui::InputFloat3("Scale", scl);
    }
    ImGui::End();

    ImGui::Begin("Post Processing");
    {
        ImGui::SliderFloat("Exposure", &exposure, 0.0f, 14.0f);
        ImGui::SliderFloat("Contrast", &contrast, 0.0f, 2.0f);
        ImGui::Checkbox("Fog", &fogEnabled);
        ImGui::ColorPicker3("Fog Color", fogColor);
        ImGui::InputFloat("Fog Density", &density);
        ImGui::Checkbox("Tone Mapping", &toneMapEnabled);
    }
    ImGui::End();


    ImGui::Begin("Project");
    {
        ImGui::Text("here's some text wowie");
        ImGui::SliderFloat("Cool Slider", &testFloat, 0.1f, 5.0f);
        ImGui::Scrollbar(ImGuiAxis_Y);
    }
    ImGui::End();

    ImGui::Begin("Console");
    {
        ImGui::Text("here's some text wowie");
        ImGui::Scrollbar(ImGuiAxis_Y);
    }
    ImGui::End();


    ImGui::Begin("Scene Graph");
    {
        if(ImGui::TreeNodeEx("SceneObject"))
        {
            if (ImGui::TreeNodeEx("ChildObject"))
            {
                ImGui::Text("testThing2");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();

	ImGui::Begin("Scene");
	{
		ImGui::BeginChild("Scene");

        if (ImGui::IsWindowHovered()) {
            sceneViewHovering = true;
        }
        else {
            sceneViewHovering = false;
        }
		ImVec2 wsize = ImGui::GetWindowSize();

		ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));


		ImGui::EndChild();
	}
	ImGui::End();

    fileBrowser.Display();

    //if (firstLoop) { firstLoop = false; }

	// Render the UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void FTEditorUI::ShowExampleAppDockSpace(bool* p_open)
{
    // READ THIS !!!
    // TL;DR; this demo is more complicated than what most users you would normally use.
    // If we remove all options we are showcasing, this demo would become:
    //     void ShowExampleAppDockSpace()
    //     {
    //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //     }
    // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
    // In this specific demo, we are not using DockSpaceOverViewport() because:
    // - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
    // - (2) we allow the host window to have padding (when opt_padding == true)
    // - (3) we expose many flags and need a way to have them visible.
    // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
    //      in your code, but we don't here because we allow the window to be floating)

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        dockspace_ID = dockspace_id;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //ShowDockingDisabledMessage();
    }


    ImGui::BeginMenuBar();
    {
        if(ImGui::BeginMenu("File", true))
        {
            if (ImGui::MenuItem("New Scene")) {

            }
            if (ImGui::MenuItem("Save Project")) {

            }
            if (ImGui::MenuItem("Import Asset")) {
                fileBrowser.Open();
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Edit", true))
        {
            if (ImGui::MenuItem("edit stuff")) {

            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help", true))
        {
            if (ImGui::MenuItem("About")) {

            }
            ImGui::EndMenu();
        }


        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void ShowDockingDisabledMessage()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton("click here"))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}


void FTEditorUI::ShutdownUI() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}