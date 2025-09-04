#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include "layers/Layer.h"

class Window
{
public:
	Window();
	~Window();
	
	bool ShouldClose();
	void Close();

	void AddLayer(std::shared_ptr<Layer> layer);

	void DrawFrame();

	ImGuiID GetMainDockspace() const {
		return m_mainDockspace;
	}

	GLFWwindow* GetWindow() {
		return m_window;
	}

private:
	std::vector<std::shared_ptr<Layer>> m_layers;
	GLFWwindow* m_window;
	ImGuiContext* m_context;
	ImGuiIO* m_io;
	ImGuiID m_mainDockspace;
};

