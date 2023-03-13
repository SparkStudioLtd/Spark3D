#include "CoreFramework.h"

void ScriptManager::reloadAssembly() {
	ScriptManager::assembly = mono_domain_assembly_open(ScriptManager::domain, "./ScriptSandbox.dll");
	ScriptManager::image = mono_assembly_get_image(ScriptManager::assembly);
}

MonoDomain* ScriptManager::domain = nullptr;
MonoAssembly* ScriptManager::assembly = nullptr;
MonoImage* ScriptManager::image = nullptr;
void ScriptManager::init() {
	mono_set_dirs("./mono/lib", "./mono/etc");

	ScriptManager::domain = mono_jit_init("SparkEngine");
	ScriptManager::reloadAssembly();
}