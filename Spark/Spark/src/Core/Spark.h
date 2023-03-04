#include "pch.h"

#include "ApplicationSpecification.h"
#include "Core/JobSystem.h"
#include "Core/AssetManager.h"
#include "Core/Graphics/Graphics.h"

class InitalizeJob : public Job {
public:
	void setup();
	void execute(Event* event);
	void clean();
};

class RenderJob : public Job {
public:
	bool firstUpdate = true;
	void setup();
	void execute(Event* event);
	void clean();
};


class Hook {
public:
	static void appReady();
};

class Spark {
public:
	static bool m_ApplicationRunning;

	static ApplicationSpecification applicationSpecification;
	static GPUContext* graphicsContext;
	static ShaderManager* shaderManager;
	static std::vector<Actor*> actors;
	static std::vector<Actor*> actorsQueue;

	static Actor* CreateActor();

	static void CreateCore();
	static void RegisterApplicationSpecification(ApplicationSpecification appSpec);
	static void EnterLoop();
	static void Shutdown();
};