#include "Device.h"

#include <algorithm>

PreparedData::~PreparedData() {
}

static PreparedData GetDevicePreparedData(HANDLE device) {
    uint32_t size = 0;

    GetRawInputDeviceInfo(device, RIDI_PREPARSEDDATA, nullptr, &size);

    PHIDP_PREPARSED_DATA data = (PHIDP_PREPARSED_DATA)malloc(size);

    GetRawInputDeviceInfo(device, RIDI_PREPARSEDDATA, data, &size);

    return PreparedData {
        .data = data,
        .len = size,
    };
}

std::string GetDeviceName(HANDLE device) {
    uint32_t nameLen = 0;

    GetRawInputDeviceInfo(device, RIDI_DEVICENAME, nullptr, &nameLen);

    TCHAR* name = new TCHAR[nameLen];

    GetRawInputDeviceInfo(device, RIDI_DEVICENAME, name, &nameLen);

    uint32_t numChars = WideCharToMultiByte(
        CP_UTF8,
        0,
        name,
        nameLen,
        nullptr,
        0,
        nullptr,
        nullptr
    );

    char* utf8Name = new char[numChars + 1];
    utf8Name[numChars] = 0;

    WideCharToMultiByte(
        CP_UTF8,
        0,
        name,
        nameLen,
        utf8Name,
        numChars,
        nullptr,
        nullptr
    );
    delete[] name;


    std::string deviceName = std::string(utf8Name);

    delete[] utf8Name;

    return deviceName;
}

constexpr size_t npos = (size_t)-1;

static std::vector<Link> GetDeviceLinks(HANDLE device, HIDP_CAPS caps, PreparedData data) {
    std::vector<Link> links;

    if (caps.NumberInputValueCaps != 0) {
        uint16_t numValCaps = caps.NumberInputValueCaps;
        HIDP_VALUE_CAPS* valueCaps = new HIDP_VALUE_CAPS[numValCaps];
        
        HidP_GetValueCaps(HidP_Input, valueCaps, &numValCaps, data.data);

        for (uint16_t i = 0; i < numValCaps; i++) {
            HIDP_VALUE_CAPS cap = valueCaps[i];

            if (cap.IsRange || !cap.IsAbsolute) {
                continue;
            }

            size_t index = npos;

            for (size_t j = 0; j < links.size(); j++) {
                if (links[j].id == cap.LinkCollection) {
                    index = j;
                    break;
                }
            }

            if (index == npos) {
                index = links.size();
                links.push_back({
                    .id = cap.LinkCollection,
                    .rect = { 0 },
                    .flags = 0,
                });
            }

            if (cap.UsagePage != HID_USAGE_PAGE_GENERIC) {
                continue;
            }

            Link& link = links[index];

            if (cap.NotRange.Usage == HID_USAGE_GENERIC_X) {
                link.flags |= LinkFlags::HasX;
                link.rect.left = cap.PhysicalMin;
                link.rect.right = cap.PhysicalMax;
            } else if (cap.NotRange.Usage == HID_USAGE_GENERIC_Y) {
                link.flags |= LinkFlags::HasY;
                link.rect.top = cap.PhysicalMin;
                link.rect.bottom = cap.PhysicalMax;
            }
        }

        for (uint16_t i = 0; i < numValCaps; i++) {
            HIDP_VALUE_CAPS cap = valueCaps[i];

            if (cap.IsRange || !cap.IsAbsolute) {
                continue;
            }

            size_t index = npos;

            for (size_t j = 0; j < links.size(); j++) {
                if (links[j].id == cap.LinkCollection) {
                    index = j;
                    break;
                }
            }

            if (index == npos) {
                index = links.size();
                links.push_back({
                    .id = cap.LinkCollection,
                    .rect = { 0 },
                    .flags = 0,
                    });
            }

            if (cap.UsagePage != HID_USAGE_PAGE_GENERIC) {
                continue;
            }

            Link& link = links[index];

            if (cap.NotRange.Usage == HID_USAGE_GENERIC_X) {
                link.flags |= LinkFlags::HasX;
                link.rect.left = cap.PhysicalMin;
                link.rect.right = cap.PhysicalMax;
            } else if (cap.NotRange.Usage == HID_USAGE_GENERIC_Y) {
                link.flags |= LinkFlags::HasY;
                link.rect.top = cap.PhysicalMin;
                link.rect.bottom = cap.PhysicalMax;
            }
        }

        delete[] valueCaps;
    }

    return links;
}

std::vector<Device> GetRegisteredDevices() {
    uint32_t numDevices = 0;
    GetRawInputDeviceList(nullptr, &numDevices, sizeof(RAWINPUTDEVICELIST));

    RAWINPUTDEVICELIST* deviceList = new RAWINPUTDEVICELIST[numDevices];

    GetRawInputDeviceList(deviceList, &numDevices, sizeof(RAWINPUTDEVICELIST));

    std::vector<Device> devices;

    for (uint32_t i = 0; i < numDevices; i++) {
        RAWINPUTDEVICELIST device = deviceList[i];
        if (device.dwType != RIM_TYPEHID) {
            continue;
        }

        PreparedData data = GetDevicePreparedData(device.hDevice);

        HIDP_CAPS caps;
        HidP_GetCaps(data.data, &caps);

        if (caps.NumberInputButtonCaps == 0) {
            continue;
        }

        std::string name = GetDeviceName(device.hDevice);
        std::vector<Link> links = GetDeviceLinks(device.hDevice, caps, data);

        Device d = Device {
            .name = std::move(name),
            .links = std::move(links),
            .data = data
        };

        devices.emplace_back(std::move(d));
    }

    delete[] deviceList;

    return devices;
}
