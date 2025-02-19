workspace "TrackpadDrawing"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    cppdialect "C++20"

    startproject "TrackpadDrawing"

    filter "configurations:Debug"
        symbols "on"
        optimize "off"
        runtime "Debug"

    filter "configurations:Release"
        symbols "off"
        optimize "on"
        runtime "Release"
    
include "GLAD"
include "GLFW"
include "ImGui"
include "TrackpadDrawing"
