project "TrackpadDrawing"
    kind "ConsoleApp"
    language "C++"

    links {
        "GLFW"
    }

    includedirs {
        "../GLFW/include/"
    }

    files {
        "src/**.cpp",
        "src/**.h"
    }
