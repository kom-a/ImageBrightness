workspace "ImageBrightness"
   configurations { "Debug", "Release" }
   architecture "x86"
   startproject "UMPK-80"

project "ImageBrightness"
    location "ImageBrightness"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Bin/")
    objdir ("Bin-int/")

    files 
    { 
        "%{prj.name}/Src/**.*",
        "%{prj.name}/Vendor/**.*",
    }

    includedirs
    {
        "%{prj.name}/Vendor/",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
