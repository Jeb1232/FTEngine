#pragma once
#include"GLFW/glfw3.h"
#include"imgui/imgui.h"
#include"imgui/imgui_internal.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include "imgui/ImGuizmo.h"
#include "imgui/imfilebrowser.h"

class FTEditorUI {
public:
	ImGui::FileBrowser fileBrowser;
	//static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	//static ImGuizmo::MODE mCurrentGizmoMode();
	float exposure = 1.0f;
	float contrast = 1.0f;
	float density;
	bool fogEnabled;
	bool toneMapEnabled;
	float fogColor[3];
	float pos[3];
	float rot[3];
	float scl[3];
	ImGuiID dockspace_ID;
	void InitUI(GLFWwindow* window);
	void NewImGuiFrame();
	void UIMainLoop();
	void ShutdownUI();
	void ShowExampleAppDockSpace(bool* p_open);
	ImGuiIO io;
	float testFloat = 1.0f;
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	unsigned int tex;
	bool sceneViewHovering;
private:
};