#include "CoreFramework.h"

void GPUSkybox::update(GPUContext* context)
{
    if (!context->renderingToDepthMap) {
        Transform* transform = new Transform();
        transform->setTransform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(100, 100, 100));
        GPUMaterial* material = new GPUMaterial();
        material->useLighting = false;
        material->albedoColor = glm::vec3(1, 1, 1);
        material->texture = nullptr;
        context->drawQueue(this->cubeMesh, Spark::shaderManager->shaders["EnvProbe"], transform, material);
    }
}