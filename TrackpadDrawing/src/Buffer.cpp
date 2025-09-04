#include "Buffer.h"

Buffer::Buffer(size_t size)
	: m_buffer(new uint8_t[size]),
	m_size(size)
{
}

Buffer::~Buffer() {
	delete[] m_buffer;
}
