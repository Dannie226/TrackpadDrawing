#pragma once

#include <cstdint>

class Notepad {
public:
	Notepad();
	~Notepad();

	void DrawImage();
	void Resize(uint32_t width, uint32_t height);

private:
	void RenderImage();

private:
	uint32_t m_width;
	uint32_t m_height;

	uint32_t m_textureID;
	uint32_t m_framebufferID;
};

