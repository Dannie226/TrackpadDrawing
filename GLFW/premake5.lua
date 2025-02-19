project "GLFW"
    kind "StaticLib"
    language "C"

    files {
        
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",

        "src/*.h",
        "src/*.c"
    }

    defines {
        "_GLFW_WIN32",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"
        
    filter "configurations:Release"
        optimize "on"
        runtime "Release"