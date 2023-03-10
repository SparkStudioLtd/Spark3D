#include "pch.h"
#include "Core/Spark.h"
#include <Core/ModelLoader.h>

void InitalizeJob::setup() {
	this->m_DebugName = "Initalize";
	this->m_executeType = ONCE;
	this->m_syncType = SYNC;
}

class Renderer : public Component {
public:
	GPUMesh* mesh;
	GPUMaterial* material;
	virtual void BeginPlay(Actor* actor) {

	}
	virtual void Update(Actor* actor) {

	}
	virtual void Render(GPUContext* context, Actor* actor) {
		if (context->renderingToDepthMap) {
			context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("ShadowPass"), actor->transform, this->material);
		}
		else {
			context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("GBuffer"), actor->transform, this->material);
		}
	}
};

void InitalizeJob::execute(Event* event) {
	AssetManager::loadFromFolder();

	Spark::graphicsContext->window = new GPUWindow();
	Spark::graphicsContext->window->createWindow(Spark::applicationSpecification.Name, Spark::applicationSpecification.Width, Spark::applicationSpecification.Height);

	Spark::graphicsContext->viewport = new GPUViewport();
	Spark::graphicsContext->viewport->position = glm::vec2(0, 0);
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(Spark::graphicsContext->window->unbaseVars["windowHandle"].get<GLFWwindow*>(), &frameBufferWidth, &frameBufferHeight);
	Spark::graphicsContext->viewport->scale = glm::vec2((float)frameBufferWidth, (float)frameBufferHeight);

	Spark::graphicsContext->createAdapterAndContext();

	Hook::appReady();

	Actor* actora = Spark::CreateActor();

	std::string graphicsApi = "opengl";
	std::string vertexShaderExt = "vert";
	std::string fragmentShaderExt = "frag";
#ifdef SPARK_VULKAN
	graphicsApi = "vulkan";
	vertexShaderExt = "vertbin";
	fragmentShaderExt = "fragbin";
#endif
	//main render pass
	Spark::graphicsContext->createRenderPass(true, nullptr, true);

	Spark::shaderManager->shaders["GBuffer"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/GBuffer." + vertexShaderExt, "./res/" + graphicsApi + "/GBuffer." + fragmentShaderExt);
	Spark::shaderManager->shaders["ShadowPass"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/ShadowPass." + vertexShaderExt, "./res/" + graphicsApi + "/ShadowPass." + fragmentShaderExt);
	Spark::shaderManager->shaders["EnvProbe"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/EnvProbe." + vertexShaderExt, "./res/" + graphicsApi + "/EnvProbe." + fragmentShaderExt);

	Spark::graphicsContext->shadowFramebuffer = Spark::graphicsContext->createFramebuffer(DEPTHMAP);
	Spark::graphicsContext->mainFramebuffer = Spark::graphicsContext->createFramebuffer(COLORMAP);
	Spark::graphicsContext->createRenderPass(false, Spark::graphicsContext->mainFramebuffer,false);


	Spark::graphicsContext->createAtmosphere();

	this->log("Initalized engine");
}

void InitalizeJob::clean() {

}