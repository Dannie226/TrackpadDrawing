#include "Notepad.h"

#include <glad/glad.h>

Notepad::Notepad() {
	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glCreateFramebuffers(1, &m_framebufferID);
}

Notepad::~Notepad() {
	glDeleteTextures(1, &m_textureID);
	glDeleteFramebuffers(1, &m_framebufferID);
}
