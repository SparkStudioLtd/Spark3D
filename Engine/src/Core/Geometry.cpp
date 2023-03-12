#include "CoreFramework.h"

void Geometry::init()
{
	this->cube = ModelLoader::loadMesh(Spark::graphicsContext, "./res/cube.obj");
}

Renderer* Geometry::getCube(GPUMaterial* material)
{
	Renderer* renderer = new Renderer();
	if (material != nullptr) {
		renderer->setMaterial(material);
	}
	else {
		GPUMaterial* material = new GPUMaterial();
		material->useLighting = true;
		material->texture = nullptr;
		material->albedoColor = glm::vec3(1, 1, 1);
		renderer->setMaterial(material);
	}
	renderer->setMesh(this->cube);
	return renderer;
}
