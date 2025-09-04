#pragma once

#include "Layer.h"

#include "../input/Touchpad.h"

class NotepadLayer : public Layer
{
public:
	NotepadLayer() = default;
	~NotepadLayer() = default;
	
	void OnAttach(Window* window) override;
	void OnRender(Window* window) override;

	void StartDrawing() { m_isDrawing = true; }
	void StopDrawing() { m_isDrawing = false; }
	void ToggleDrawing() { m_isDrawing = !m_isDrawing; }
	bool IsDrawing() const { return m_isDrawing; }

	Touchpad& GetTouchpad() { return m_touchpad; }
	void ReadTouchLocation(RAWINPUT* input) { m_location = m_touchpad.GetTouchLocation(input); }
	TouchLocation GetTouchLocation() const { return m_location; }

private:
	bool m_isDrawing = false;
	Touchpad m_touchpad;
	TouchLocation m_location = { 0 };
};

