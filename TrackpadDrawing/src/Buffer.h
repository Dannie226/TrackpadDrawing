#pragma once

#include <cstdint>

class Buffer
{
public:
	Buffer(size_t size);
	~Buffer();

	size_t Size() const { return m_size; }

	const uint8_t* Get() const { return m_buffer; }
	uint8_t* Get() { return m_buffer; }

	uint8_t& operator[] (size_t index) { return m_buffer[index]; };

private:
	uint8_t* m_buffer;
	size_t m_size;
};

