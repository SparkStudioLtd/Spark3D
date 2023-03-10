#include "CoreFramework.h"

void GPUBuffer::bind(GPUContext* context)
{
    int buffer = std::any_cast<int>(this->unbaseVars["bufferID"]);

    switch (this->bufferType) {
    case VERTEXBUFFER:
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        break;
    case INDEXBUFFER:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        break;
    case SHADERINPUTBUFFER:
        break;
    }
}

void GPUBuffer::uploadData(GPUContext* context, const void* data, int size)
{
    //to fix
    int buffer = std::any_cast<int>(this->unbaseVars["bufferID"]);

    this->bind(context);

    switch (this->bufferType) {
    case VERTEXBUFFER:
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        break;
    case INDEXBUFFER:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        break;
    case SHADERINPUTBUFFER:
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
        break;
    }

    this->unbind();
}

void GPUBuffer::unbind()
{
    int buffer = std::any_cast<int>(this->unbaseVars["bufferID"]);

    switch (this->bufferType) {
    case VERTEXBUFFER:
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        break;
    case INDEXBUFFER:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        break;
    case SHADERINPUTBUFFER:
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        break;
    }
}