#include "Core/Graphics/Graphics.h"

void GPUFramebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, std::any_cast<int>(this->unbaseVars["framebufferID"]));
}

void GPUFramebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}