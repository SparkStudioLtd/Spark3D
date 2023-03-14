#include "CoreFramework.h"

MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
{
    MonoImage* image = mono_assembly_get_image(assembly);
    MonoClass* klass = mono_class_from_name(image, namespaceName, className);

    if (klass == nullptr)
    {
        // Log error here
        return nullptr;
    }

    return klass;
}

MonoSparkScript* CreateScript(std::string className) {
    MonoClass* klass = GetClassInAssembly(ScriptManager::assembly, "Sandbox", className.c_str());
    MonoObject* instance = mono_object_new(ScriptManager::domain,klass);
    mono_runtime_object_init(instance);
    MonoSparkScript* script = new MonoSparkScript();
    script->m_MonoName = className;
    script->m_Instance = instance;
    return script;
}

void ScriptManager::reloadAssembly() {
	ScriptManager::assembly = mono_domain_assembly_open(ScriptManager::domain, "./ScriptSandbox.dll");
	ScriptManager::image = mono_assembly_get_image(ScriptManager::assembly);

    ScriptManager::m_Scripts["TestComponent"] = CreateScript("TestComponent");
}

MonoDomain* ScriptManager::domain = nullptr;
MonoAssembly* ScriptManager::assembly = nullptr;
MonoImage* ScriptManager::image = nullptr;
std::map<std::string, MonoSparkScript*> ScriptManager::m_Scripts = std::map<std::string, MonoSparkScript*>();
void ScriptManager::init() {
	mono_set_dirs("./mono/lib", "./mono/etc");

	ScriptManager::domain = mono_jit_init("SparkEngine");
	ScriptManager::reloadAssembly();
}