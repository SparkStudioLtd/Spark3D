#include "CoreFramework.h"

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void GPURenderPass::begin(GPUContext* context) {

    context->activeShader = this->attachedShader;
    if (this->useFramebuffer)
    {
        this->framebuffer->bind();
        if (this->framebuffer->type == DEPTHMAP) {
            context->renderingToDepthMap = true;
        }
    }
    else {
        //BLUR!!!!!!12.03.2023
        //two pass blur13.03.2023
        //im getting depression14.03.2023
        
        GPUFramebuffer* hBuffer = Spark::graphicsContext->blurTechnique[0];
        GPUFramebuffer* vBuffer = Spark::graphicsContext->blurTechnique[1];

        Spark::shaderManager->shaderByName("Blur")->bind();

        hBuffer->bind();
        Spark::shaderManager->shaderByName("Blur")->shaderInputDataInt("horizontal", true);
        glBindTexture(GL_TEXTURE_2D, std::any_cast<int>(context->mainFramebuffer->unbaseVars["emissionColorBuffer"]));
        renderQuad();
        GPUFramebuffer::unbind();

        vBuffer->bind();
        Spark::shaderManager->shaderByName("Blur")->shaderInputDataInt("horizontal", false);
        glBindTexture(GL_TEXTURE_2D, std::any_cast<int>(vBuffer->unbaseVars["textureColorBuffer"]));
        renderQuad();
        GPUFramebuffer::unbind();

        GPUShader::unbind();
    }
    glViewport(0, 0, this->customViewport.x, this->customViewport.y);
    glClearColor(context->clearColor.red, context->clearColor.green, context->clearColor.blue, context->clearColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);
    if (this->useFramebuffer)
        if (this->framebuffer->type == DEPTHMAP)
        {
            //glCullFace(GL_FRONT_AND_BACK);
        }

    //if (!this->useFramebuffer) {
    if (context->skybox != nullptr && !this->disallowToRenderNotPriorityItems) {
        //if (this->framebuffer != nullptr) {
            //if (this->framebuffer->type != DEPTHMAP) {
        if (this->renderSkybox) {
            context->skybox->update(context);
        }
        //}
   // }
    //else {
    //    context->skybox->update(instance, context);
    //}
    }
    //}
}


void GPURenderPass::end(GPUContext* context) {
    GLFWwindow* window = context->window->unbaseVars["windowHandle"].get<GLFWwindow*>();


    glViewport(0, 0, context->window->width, context->window->height);
    if (context->useGui && this->renderSkybox)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glViewport(context->viewport->position.x, context->viewport->position.y, context->viewport->scale.x, context->viewport->scale.y);

    for (GPUDrawData* drawData : context->drawQueueList) {
        drawData->mesh->drawDirect(context,drawData->shader, drawData->material, drawData->transform);
        delete drawData;
    }

    //Draw bloom/postprocessing
    if (context->activeShader == Spark::shaderManager->shaderByName("PostProcess")) {
        GPUMaterial* material = new GPUMaterial();
        GPUTexture* computeFramebuffer = new GPUTexture();
        computeFramebuffer->unbaseVars["textureID"] = std::any_cast<int>(Spark::graphicsContext->blurTechnique[1]->unbaseVars["textureColorBuffer"]);
        material->texture = computeFramebuffer;
        material->useLighting = false;
        material->albedoColor = glm::vec3(0, 0, 0);
        Transform* transform = new Transform();
        transform->setTransform(glm::vec3(0), glm::vec3(0), glm::vec3(0));
        context->layerQuad->drawDirect(context, Spark::shaderManager->shaderByName("PostProcess"), material, transform);
        delete material;
        delete computeFramebuffer;
        delete transform;
    }

    //finally 04.03.2023 12:59 first skybox on new base!!!!!!!!!!!
    if (this->useFramebuffer) {
        GPUFramebuffer::unbind();
        if (this->framebuffer->type == DEPTHMAP) {
            context->renderingToDepthMap = false;
            //glCullFace(GL_FRONT);
        }
    }

    //clear draw queue
    context->drawQueueList.clear();
}
