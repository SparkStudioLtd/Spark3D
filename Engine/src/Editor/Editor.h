#include "Editor/Panels/ActorInfoPanel.hpp"
#include "Editor/Panels/ViewportPanel.hpp"
#include "Editor/Panels/ScenePanel.hpp"
#include "Editor/Panels/ContentPanel.hpp"
#include "Editor/Panels/PerformancePanel.hpp"
#include "Editor/Panels/ToolboxPanel.hpp"

class ViewportCameraInfo {
public:
	bool mouseHooked = false;
	float lastX = 0, lastY = 0;
};

class Editor {
public:
	Actor* selectedActor;
	ViewportCameraInfo* viewportCamera = new ViewportCameraInfo();
	PanelManager* panelManager = new PanelManager();
	void init();
	void render();
    
};