#include "Editor.h"

void Hook::appReady() {
	Actor* actora = Spark::CreateActor();

	GPUMaterial* material = new GPUMaterial();
	material->albedoColor = glm::vec3(1, 1, 1);
	material->texture = nullptr;
	material->useLighting = true;
	actora->transform->position = glm::vec3(0, 0, -5);

	Renderer* renderer = new Renderer();
	renderer->material = material;
	renderer->mesh = ModelLoader::loadMesh(Spark::graphicsContext, "./res/cube.obj");
	actora->addComponent(renderer);
	//actora->addComponent(new Monkey());
}