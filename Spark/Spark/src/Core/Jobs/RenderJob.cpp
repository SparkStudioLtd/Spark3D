#include "pch.h"
#include "Core/Spark.h"

void RenderJob::setup() {
	this->m_DebugName = "Render";
	this->m_executeType = EVENTHANDLER;
	this->m_syncType = SYNC;
}

void RenderJob::execute(Event* event) {
	if (event->m_EventType != UPDATE)
		return;


	Spark::graphicsContext->begin();
	Spark::graphicsContext->frameCount++;


	if (this->firstUpdate) {
		for (Actor* actor : Spark::actors) {
			for (Component* component : actor->components) {
				component->BeginPlay(actor);
			}
		}
		this->firstUpdate = false;
	}

	//update deltatime:skull:
#ifdef SPARK_OPENGL
	float currentFrame = glfwGetTime();
	this->graphicsContext->deltaTime = currentFrame - this->graphicsContext->lastFrame;
	this->graphicsContext->lastFrame = currentFrame;
#endif

	Spark::graphicsContext->camera->update(Spark::graphicsContext);

	for (Actor* actor : Spark::actors) {
		for (Component* component : actor->components) {
			component->Update(actor);
		}
	}

	for (GPURenderPass* renderPass : Spark::graphicsContext->renderPasses) {
		renderPass->begin(Spark::graphicsContext);

		for (Actor* actor : Spark::actors) {
			for (Component* component : actor->components) {
				if (renderPass->disallowToRenderNotPriorityItems) {
					if (component->priorityRendering) {
						component->Render(Spark::graphicsContext, actor);
					}
				}
				else {
					component->Render(Spark::graphicsContext, actor);
				}
			}
		}


		renderPass->end(Spark::graphicsContext);
	}

	Spark::graphicsContext->end();

	for (Actor* actorInQueue : Spark::actorsQueue) {
		Spark::actors.push_back(actorInQueue);
	}
	Spark::actorsQueue.clear();



	//this->log("Polling events");
	glfwPollEvents();
	//this->log("Swaping Buffers");
	glfwSwapInterval(0);
	glfwSwapBuffers(Spark::graphicsContext->window->unbaseVars["windowHandle"].get<GLFWwindow*>());
}

void RenderJob::clean() {

}