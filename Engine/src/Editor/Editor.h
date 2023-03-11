#include "Editor/Panels/ActorInfoPanel.hpp"
#include "Editor/Panels/ViewportPanel.hpp"
#include "Editor/Panels/ScenePanel.hpp"
#include "Editor/Panels/ContentPanel.hpp"
#include "Editor/Panels/PerformancePanel.hpp"
#include "Editor/Panels/ToolboxPanel.hpp"


class Editor {
public:
	Actor* selectedActor;
	PanelManager* panelManager = new PanelManager();
	void init();
	void render();
    
};