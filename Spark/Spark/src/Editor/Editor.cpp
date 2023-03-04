#include "Editor.h"

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

class Monkey : public Component {
public:
	virtual void BeginPlay(Actor* actor) {

	}
	virtual void Update(Actor* actor) {

	}
	virtual void Render(GPUContext* context, Actor* actor) {
		actor->transform->rotation += 0.5f;
	}
};

void Hook::appReady() {
	Actor* actora = Spark::CreateActor();

	GPUMaterial* material = new GPUMaterial();
	material->albedoColor = glm::vec3(1, 1, 1);
	material->texture = nullptr;
	material->useLighting = true;
	actora->transform->scale = glm::vec3(0.6f, 0.6f, 0.6f);
	actora->transform->position = glm::vec3(0, -0.3f, -5);
	actora->transform->rotation = glm::vec3(0, 70, 0);
	

	Renderer* renderer = new Renderer();
	renderer->material = material;
	renderer->mesh = ModelLoader::loadMesh(Spark::graphicsContext, "./res/cube.obj");
	actora->addComponent(renderer);
	actora->addComponent(new Monkey());
}