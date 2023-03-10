#include "pch.h"
#include "ModelLoader.h"
#include "Spark.h"

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

class Geometry {
public:
	void init();
	Renderer* getCube(GPUMaterial* material = nullptr);
private:
	GPUMesh* cube;
};