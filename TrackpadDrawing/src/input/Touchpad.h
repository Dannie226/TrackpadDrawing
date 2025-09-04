#pragma once

#include <cstdint>

#include "Device.h"

struct TouchLocation
{
	uint32_t x;
	uint32_t y;
};

class Touchpad
{
public:
	Touchpad();
	~Touchpad() = default;

	bool HasCached() const { return m_deviceIndex != (size_t)-1; }
	TouchLocation GetTouchLocation(PRAWINPUT input);

	void CacheDevice(const char* name);
private:
	std::vector<Device> m_devices;
	size_t m_deviceIndex = (size_t)-1;
};

