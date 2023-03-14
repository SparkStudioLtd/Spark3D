#include "CoreFramework.h"

void GPUMesh::drawDirect(GPUContext* context, GPUShader* shader, GPUMaterial* material, Transform* transform)
{
    shader->bind();



    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform->getPosition());
    model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));
    model = glm::scale(model, transform->getScale());

    shader->shaderInputDataMat4("model", model);
    shader->shaderInputDataMat4("projection", context->camera->getProjectionMatrix(context));
    shader->shaderInputDataMat4("view", context->camera->getViewMatrix(context));

    shader->shaderInputDataInt("useTexture", material->texture == nullptr ? 0 : 1);
    shader->shaderInputDataVec3("albedoColor", material->albedoColor);
    shader->shaderInputDataInt("useLighting", material->useLighting ? 1 : 0);


    //lighting
    shader->shaderInputDataVec3("lightColor", glm::vec3(1, 1, 1));
    shader->shaderInputDataVec3("lightDire", glm::vec3(0,10,0));
    shader->shaderInputDataVec3("eyePos", context->camera->position);

    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    shader->shaderInputDataMat4("lightSpaceMatrix", lightProjection * lightView);

    if (shader == Spark::shaderManager->shaderByName("PostProcess")) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, std::any_cast<int>(context->mainFramebuffer->unbaseVars["textureColorBuffer"]));
        shader->shaderInputDataInt("depthMap", 0);
    }
    else {

    }


    int meshLayout = std::any_cast<int>(this->unbaseVars["meshLayout"]);
    int textureID = 0;
    if (material->texture != nullptr) {
        textureID = std::any_cast<int>(material->texture->unbaseVars["textureID"]);
    }
    glBindVertexArray(meshLayout);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader->shaderInputDataInt("texSampler", 1);
    this->indexBuffer->bind(context);
    //glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
    glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, 0);
    this->indexBuffer->unbind();
    glBindVertexArray(0);
    GPUShader::unbind();
}