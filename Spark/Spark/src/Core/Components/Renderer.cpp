#include "Renderer.h"


void Renderer::BeginPlay(Actor* actor)
{
}

void Renderer::Update(Actor* actor)
{
}

void Renderer::Render(GPUContext* context, Actor* actor)
{
	if (context->renderingToDepthMap) {
		context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("ShadowPass"), actor->transform, this->material);
	}
	else {
		context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("GBuffer"), actor->transform, this->material);
	}
}
