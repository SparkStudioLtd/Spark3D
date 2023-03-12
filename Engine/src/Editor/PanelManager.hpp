#include "pch.h"
#include <imgui/imgui_stdlib.h>
#include <imgui/imgui_internal.h>
#include <CoreFramework.h>

class Panel {
public:
	Obj editor;
	Actor* selectedActor;
	std::string m_Name;
	bool m_Show;
	virtual void render() {
	}
};

class PanelManager {
public:
	std::vector<Panel*> m_Panels;
	template<typename T> void registerPanel(std::string name, bool show) {
		T* clazz = new T();
		clazz->m_Name = name;
		clazz->m_Show = show;
		m_Panels.push_back(clazz);
	}
};

