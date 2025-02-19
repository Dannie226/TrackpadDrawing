project "ImGui"
    kind "StaticLib"
    language "C++"

    files {
        "*.cpp",
        "*.h",

        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_opengl3.h"
    }

    includedirs {
        "./",
        "../GLFW/include/",
    }
