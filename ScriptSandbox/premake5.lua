project "ScriptSandbox"
    kind "SharedLib"
    language "C#"
    targetdir "../Binaries/build/Script"
    objdir "../Binaries/build/Script_obj"
    architecture "x64"

    debugdir "../Runtime"

    postbuildcommands {
        "{COPY} ./ScriptSandbox.dll ../../../Runtime"
    }


    files { "**.cs" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"