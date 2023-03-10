#include "CoreFramework.h"

glm::mat4 Camera::getProjectionMatrix(GPUContext* context)
{
    return glm::perspective(glm::radians(45.0f), (float)context->window->width / (float)context->window->height, 0.1f, 1000.0f);
}



glm::mat4 Camera::getViewMatrix(GPUContext* context)
{
    glm::vec3 position = this->position;
    glm::vec3 rotationVec = glm::vec3(glm::radians(this->rotation.x), glm::radians(this->rotation.y), glm::radians(this->rotation.z));
    auto rotation = glm::quat(glm::vec3(rotationVec.x, rotationVec.y, rotationVec.z));
    auto r = glm::mat4_cast(rotation);
    auto t = glm::translate(glm::mat4(1.f), position);
    auto view = glm::affineInverse(t * r);
    return view;
}

void Camera::update(GPUContext* context)
{
    if (this->allowDrone) {

    }
}
