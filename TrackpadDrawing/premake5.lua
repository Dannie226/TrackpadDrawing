project "TrackpadDrawing"
    kind "ConsoleApp"
    language "C++"

    links {
        "GLFW",
        "GLAD"
    }

    includedirs {
        "../GLFW/include/",
        "../GLAD/include/"
    }

    files {
        "src/**.cpp",
        "src/**.h"
    }
