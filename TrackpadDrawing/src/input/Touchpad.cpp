#include "Touchpad.h"

Touchpad::Touchpad()
	: m_devices(std::move(GetRegisteredDevices())) { }

void Touchpad::CacheDevice(const char* name) {
	if (HasCached()) {
		return;
	}

	for (size_t i = 0; i < m_devices.size(); i++) {
		Device& device = m_devices[i];
		if (device.name == name) {
			m_deviceIndex = i;
			return;
		}
	}
}

TouchLocation Touchpad::GetTouchLocation(PRAWINPUT input) {
	if (!HasCached()) {
		return { 0 };
	}

	Device& d = m_devices[m_deviceIndex];

	for (auto& link : d.links) {
		if ((link.flags & LinkFlags::HasX) != 0 && (link.flags & LinkFlags::HasY) != 0) {
			ULONG usageValue;

			HidP_GetUsageValue(
				HidP_Input,
				HID_USAGE_PAGE_GENERIC,
				link.id,
				HID_USAGE_GENERIC_X,
				&usageValue,
				d.data.data,
				(char*) input->data.hid.bRawData,
				input->data.hid.dwSizeHid
			);

			uint32_t x = usageValue;

			HidP_GetUsageValue(
				HidP_Input,
				HID_USAGE_PAGE_GENERIC,
				link.id,
				HID_USAGE_GENERIC_Y,
				&usageValue,
				d.data.data,
				(char*)input->data.hid.bRawData,
				input->data.hid.dwSizeHid
			);

			return {
				.x = x,
				.y = usageValue
			};
		}
	}

	return { 0 };
}
