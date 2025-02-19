project "TrackpadDrawing"
    kind "ConsoleApp"
    language "C++"

    links {
        "GLFW",
        "GLAD",
        "ImGui"
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
