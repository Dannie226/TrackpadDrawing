#pragma once

#include <Windows.h>
#include <hidusage.h>
#include <hidpi.h>

#include <string>
#include <vector>

struct PreparedData
{
	~PreparedData();
	PHIDP_PREPARSED_DATA data;
	uint32_t len;
};

struct Link
{
	uint16_t id;
	RECT rect;
	uint32_t flags;
};

struct Device
{
	std::string name;
	std::vector<Link> links;
	PreparedData data;
};

enum LinkFlags
{
	HasX = 1,
	HasY = 2,
    HasContactID = 4,
    HasTipSwitch = 8,
    HasConfidence = 16,
    HasWidth = 32,
    HasHeight = 64,
    HasPressure = 128
};

std::string GetDeviceName(HANDLE device);
std::vector<Device> GetRegisteredDevices();