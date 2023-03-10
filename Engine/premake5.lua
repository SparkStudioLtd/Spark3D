project "Engine"
    kind "ConsoleApp"
    language "C++"
    targetdir "../Binaries/build/Engine"
    objdir "../Binaries/build/Engine_obj"
    cppdialect "C++17"
    architecture "x64"

    libdirs {
        "../Libraries/"
    }

    includedirs {
        "../Engine/src",
        "../Engine/src/Thirdparty"
    }

    debugdir "../Runtime"

    links {
        "assimp-vc143-mtd.lib","glfw3.lib","liblz4_static.lib"
    }

    files { "**.h", "**.cpp", "**.c","**.hpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"