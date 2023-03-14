#include "CoreFramework.h"



Actor* Spark::CreateActor()
{
	Actor* actor = new Actor();
	actor->transform = new Transform();
	actor->transform->setTransform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	actor->transform->name = "Transform";
	actor->addComponent(actor->transform);
	Spark::actors.push_back(actor);
	return actor;
}

Actor* Spark::CreateActorInQueue()
{
	Actor* actor = new Actor();
	actor->transform = new Transform();
	actor->transform->setTransform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	actor->transform->name = "Transform";
	actor->addComponent(actor->transform);
	Spark::actorsQueue.push_back(actor);
	return actor;
}

void Spark::CreateCore() {
	JobSystem::AddJob(new InitalizeJob());
	JobSystem::AddJob(new RenderJob());
}

template<typename T>
T* Actor::getComponent()
{
	for (Component* component : this->components) {
		if (instanceof<T*>(component)) {
			return component;
		}
	}
}

void Spark::RegisterApplicationSpecification(ApplicationSpecification app) {
	Spark::applicationSpecification = app;
}

bool Spark::m_ApplicationRunning = true;
GPUContext* Spark::graphicsContext = new GPUContext();
ShaderManager* Spark::shaderManager = new ShaderManager();
std::vector<Actor*> Spark::actors = std::vector<Actor*>();
std::vector<Actor*> Spark::actorsQueue = std::vector<Actor*>();
Geometry* Spark::geometry = new Geometry();
ApplicationSpecification Spark::applicationSpecification = ApplicationSpecification();
int Spark::framesPerSecound = 0;
std::string Spark::graphicsRendererVendor = "";
std::string Spark::graphicsVendor = "";
void Spark::EnterLoop() {
	std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();
	int m_Fps = 0;
	while (m_ApplicationRunning) {
		auto currentTime = std::chrono::steady_clock::now();
		const auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
		++m_Fps;
		if (elapsedTime > 1000000000) {
			lastTime = currentTime;
			Spark::framesPerSecound = m_Fps;
			m_Fps = 0;
		}
		JobSystem::update();
		//Vendor info
		if (Spark::graphicsRendererVendor == "" && Spark::graphicsVendor == "") {
			const GLubyte* tmp;
			tmp = glGetString(GL_VENDOR);
			Spark::graphicsVendor = reinterpret_cast<const char*>(const_cast<GLubyte*>(tmp));
			tmp = glGetString(GL_RENDERER);
			Spark::graphicsRendererVendor = reinterpret_cast<const char*>(const_cast<GLubyte*>(tmp));
		}
	}
}

void Spark::Shutdown() {
	JobSystem::clean();
}