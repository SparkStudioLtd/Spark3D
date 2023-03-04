#include "Spark.h"




Actor* Spark::CreateActor()
{
	Actor* actor = new Actor();
	Spark::actors.push_back(actor);
	return actor;
}

void Spark::CreateCore() {
	JobSystem::AddJob(new InitalizeJob());
	JobSystem::AddJob(new RenderJob());
}

void Spark::RegisterApplicationSpecification(ApplicationSpecification app) {
	Spark::applicationSpecification = app;
}

bool Spark::m_ApplicationRunning = true;
GPUContext* Spark::graphicsContext = new GPUContext();
ShaderManager* Spark::shaderManager = new ShaderManager();
std::vector<Actor*> Spark::actors = std::vector<Actor*>();
std::vector<Actor*> Spark::actorsQueue = std::vector<Actor*>();
ApplicationSpecification Spark::applicationSpecification = ApplicationSpecification();
void Spark::EnterLoop() {
	while (m_ApplicationRunning) {
		JobSystem::update();
	}
}

void Spark::Shutdown() {
	JobSystem::clean();
}