#include "CoreFramework.h"

void InitalizeJob::setup() {
	this->m_DebugName = "Initalize";
	this->m_executeType = ONCE;
	this->m_syncType = SYNC;
}


void InitalizeJob::execute(Event* event) {
	AssetManager::reload();
	ScriptManager::init();

	Spark::graphicsContext->window = new GPUWindow();
	Spark::graphicsContext->window->createWindow(Spark::applicationSpecification.Name, Spark::applicationSpecification.Width, Spark::applicationSpecification.Height);

	Spark::graphicsContext->viewport = new GPUViewport();
	Spark::graphicsContext->viewport->position = glm::vec2(0, 0);
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(Spark::graphicsContext->window->unbaseVars["windowHandle"].get<GLFWwindow*>(), &frameBufferWidth, &frameBufferHeight);
	Spark::graphicsContext->viewport->scale = glm::vec2((float)frameBufferWidth, (float)frameBufferHeight);

	Spark::graphicsContext->createAdapterAndContext();

	AssetManager::loadAssetHandles();
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
	Spark::shaderManager->shaders["GBuffer"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/GBuffer." + vertexShaderExt, "./res/" + graphicsApi + "/GBuffer." + fragmentShaderExt);
	Spark::shaderManager->shaders["ShadowPass"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/ShadowPass." + vertexShaderExt, "./res/" + graphicsApi + "/ShadowPass." + fragmentShaderExt);
	Spark::shaderManager->shaders["EnvProbe"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/EnvProbe." + vertexShaderExt, "./res/" + graphicsApi + "/EnvProbe." + fragmentShaderExt);
	Spark::shaderManager->shaders["PostProcess"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/PostProcess." + vertexShaderExt, "./res/" + graphicsApi + "/PostProcess." + fragmentShaderExt);
	Spark::shaderManager->shaders["Blur"] = Spark::graphicsContext->createShader("./res/" + graphicsApi + "/Blur." + vertexShaderExt, "./res/" + graphicsApi + "/Blur." + fragmentShaderExt);

	//main render pass
#ifdef SPARK_EDITOR
	Spark::graphicsContext->createRenderPass(true, nullptr, true, Spark::shaderManager->shaderByName("GBuffer"));
#else
	Spark::graphicsContext->createRenderPass(true, nullptr, false);
#endif

	Spark::graphicsContext->shadowFramebuffer = Spark::graphicsContext->createFramebuffer(DEPTHMAP,false);
	Spark::graphicsContext->mainFramebuffer = Spark::graphicsContext->createFramebuffer(COLORMAP,true);
	Spark::graphicsContext->layerFramebuffer = Spark::graphicsContext->createFramebuffer(COLORMAP,false);
	Spark::graphicsContext->createRenderPass(false, Spark::graphicsContext->layerFramebuffer, true, Spark::shaderManager->shaderByName("PostProcess"));
	Spark::graphicsContext->renderPasses[1]->renderSkybox = false;
#ifdef SPARK_EDITOR
	Spark::graphicsContext->createRenderPass(false, Spark::graphicsContext->mainFramebuffer, false,Spark::shaderManager->shaderByName("GBuffer"));
#endif


	unsigned int pingpongFBO[2];
	unsigned int pingpongBuffer[2];
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongBuffer);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0
		);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	Spark::graphicsContext->blurTechnique[0] = new GPUFramebuffer();
	Spark::graphicsContext->blurTechnique[0]->unbaseVars["framebufferID"] = (int)pingpongFBO[0];
	Spark::graphicsContext->blurTechnique[0]->unbaseVars["textureColorBuffer"] = (int)pingpongBuffer[0];
	Spark::graphicsContext->blurTechnique[1] = new GPUFramebuffer();
	Spark::graphicsContext->blurTechnique[1]->unbaseVars["framebufferID"] = (int)pingpongFBO[1];
	Spark::graphicsContext->blurTechnique[1]->unbaseVars["textureColorBuffer"] = (int)pingpongBuffer[1];

	Spark::graphicsContext->createAtmosphere();

	Spark::geometry->init();

	this->log("Initalized engine");
}

void InitalizeJob::clean() {

}