project "TrackpadDrawing"
    kind "ConsoleApp"
    language "C++"

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "Comctl32.lib",
        "hid.lib"
    }

    includedirs {
        "../GLFW/include/",
        "../GLAD/include/",
        "../ImGui/"
    }

    files {
        "src/**.cpp",
        "src/**.h"
    }
