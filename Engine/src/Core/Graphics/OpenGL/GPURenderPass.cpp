#include "CoreFramework.h"

void GPURenderPass::begin(GPUContext* context) {
    if (this->useFramebuffer)
    {
        this->framebuffer->bind();
        if (this->framebuffer->type == DEPTHMAP) {
            context->renderingToDepthMap = true;
        }
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
        context->skybox->update(context);
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
    if (context->useGui)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glViewport(context->viewport->position.x, context->viewport->position.y, context->viewport->scale.x, context->viewport->scale.y);

    context->activeShader = this->attachedShader;
    for (GPUDrawData* drawData : context->drawQueueList) {
        drawData->mesh->drawDirect(context, drawData->shader, drawData->material, drawData->transform);
        delete drawData;
    }
    context->activeShader = nullptr;
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
