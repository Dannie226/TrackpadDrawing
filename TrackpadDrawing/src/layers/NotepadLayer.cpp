#include "NotepadLayer.h"

#include <exception>
#include <iostream>

#include <Windows.h>
#include <hidusage.h>
#include <commctrl.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "../Buffer.h"
#include "../input/Device.h"

void NotepadLayer::OnRender(Window* window) {
    ImGui::SetNextWindowDockID(window->GetMainDockspace());
    ImGui::Begin("Note Sheet", nullptr, ImGuiWindowFlags_NoTitleBar);

    if (this->IsDrawing()) {
        ImGui::Text("Drawing!");
        TouchLocation loc = GetTouchLocation();
        ImGui::Text("X: %d, Y: %d", loc.x, loc.y);
    } else {
        ImGui::Text("Not Drawing!");
    }

    ImGui::End();
}

void HandleRawInput(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam,
    void* refData
) {
    HRAWINPUT rawData = (HRAWINPUT)lParam;
    uint32_t dataSize = 0;

    GetRawInputData(rawData, RID_INPUT, nullptr, &dataSize, sizeof(RAWINPUTHEADER));

    Buffer dataBuffer(dataSize);
    GetRawInputData(rawData, RID_INPUT, dataBuffer.Get(), &dataSize, sizeof(RAWINPUTHEADER));

    RAWINPUT* input = (RAWINPUT*)dataBuffer.Get();
    NotepadLayer* layer = (NotepadLayer*)refData;

    if (!layer->IsDrawing()) {
        return;
    }

    if (input->header.dwType != RIM_TYPEHID) {
        return;
    }

    if (!layer->GetTouchpad().HasCached()) {
        std::string name = GetDeviceName(input->header.hDevice);
        layer->GetTouchpad().CacheDevice(name.c_str());
    }

    layer->ReadTouchLocation(input);
}

LRESULT CALLBACK RawInputSubclass(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam,
    UINT_PTR subclassId,
    DWORD_PTR refData
) {

    switch (msg) {
    case WM_INPUT:
        //std::cout << "Raw Input!" << std::endl;
        HandleRawInput(hwnd, wParam, lParam, (void*)refData);
        return 0;

    default:
        return DefSubclassProc(hwnd, msg, wParam, lParam);
    }
}

void NotepadLayer::OnAttach(Window* window) {
    HWND handle = glfwGetWin32Window(window->GetWindow());

    RAWINPUTDEVICE inputDevice = { 0 };

    inputDevice.dwFlags = RIDEV_INPUTSINK;
    inputDevice.usUsage = HID_USAGE_DIGITIZER_TOUCH_PAD;
    inputDevice.usUsagePage = HID_USAGE_PAGE_DIGITIZER;
    inputDevice.hwndTarget = handle;

    if (!RegisterRawInputDevices(&inputDevice, 1, sizeof(RAWINPUTDEVICE))) {
        throw std::exception("Failed to initialize touch pad");
    } else {
        std::cout << "Initialized touch pad" << std::endl;
    }

    SetWindowSubclass(handle, RawInputSubclass, 0, (DWORD_PTR)this);

    glfwSetWindowUserPointer(window->GetWindow(), this);

    glfwSetKeyCallback(window->GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_S && action == GLFW_PRESS) {
            NotepadLayer* layer = (NotepadLayer*)glfwGetWindowUserPointer(window);
            layer->ToggleDrawing();
        }
    });
}