#pragma once
#include "Core/Components/Transform.h"
#include "Core/Graphics/Graphics.h"
#include "Core/Spark.h"


class Renderer : public Component {
public:
	GPUMesh* mesh;
	GPUMaterial* material;
	virtual void BeginPlay(Actor* actor);
	virtual void Update(Actor* actor);
	virtual void Render(GPUContext* context, Actor* actor);
};