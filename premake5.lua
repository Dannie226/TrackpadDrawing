workspace "TrackpadDrawing"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    cppdialect "C++20"

    filter "configurations:Debug"
        symbols "on"
        optimize "off"
        runtime "Debug"

    filter "configurations:Release"
        symbols "off"
        optimize "on"
        runtime "Release"
    
    startproject "TrackpadDrawing"

include "GLAD"
include "GLFW"
include "ImGui"
include "TrackpadDrawing"
