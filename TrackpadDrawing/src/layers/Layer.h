#pragma once

class Window;

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnAttach(Window* window) { };
	virtual void OnRender(Window* window) { };
	virtual void OnDetach(Window* window) { };
};

#include "../Window.h"