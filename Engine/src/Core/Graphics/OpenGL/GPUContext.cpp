#include "CoreFramework.h"
#define STB_IMAGE_IMPLEMENTATION
#include <Thirdparty/stb_image.h>

void GPUContext::createAdapterAndContext() {

    glfwMakeContextCurrent(this->window->unbaseVars["windowHandle"].get<GLFWwindow*>());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //Debug::error("GLAD failed to load OpenGL");
    }

    glViewport(0, 0, this->window->width, this->window->height);

    Vertex vertices[] = {
        {{-1.0f,  1.0f,0.0f},{0.0f, 1.0f},{0,0,0}},
        {{-1.0f, -1.0f,0.0f},{0.0f, 0.0f},{0,0,0}},
        {{1.0f, -1.0f,0.0f},{1.0f, 0.0f},{0,0,0}},

        {{-1.0f,  1.0f,0.0f},{0.0f, 1.0f},{0,0,0}},
        {{ 1.0f, -1.0f,0.0f},{1.0f, 0.0f},{0,0,0}},
        {{1.0f,  1.0f,0.0f},{1.0f, 1.0f},{0,0,0}},
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    this->layerQuad = this->createMesh(vertices, sizeof(vertices), indices, sizeof(indices));
}


void GPUContext::begin() {
    //Create render pass
    glClearColor(this->clearColor.red, this->clearColor.green, this->clearColor.blue, this->clearColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GPUContext::end() {
    //end render pass
    GLFWwindow* window = this->window->unbaseVars["windowHandle"].get<GLFWwindow*>();

    glfwSwapInterval(1);
    glfwSwapBuffers(window);
    glfwPollEvents();
}


GPUShader* GPUContext::createShader(std::string vertex, std::string fragment)
{
    GPUShader* shader = new GPUShader();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vertex);
    fShaderFile.open(fragment);

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();


    //End load file
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);


    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error while compiling vertex shader: " + std::string(infoLog) << std::endl;
        //Debug::error("Error while compiling vertex shader: " + std::string(infoLog));
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error while compiling fragment shader: " + std::string(infoLog) << std::endl;
        //Debug::error("Error while compiling fragment shader: " + std::string(infoLog));
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        //Debug::error("Error while linking shader: " + std::string(infoLog));
    }

    shader->unbaseVars["programID"] = (int)shaderProgram;

    return shader;
}

GPUBuffer* GPUContext::createBuffer(GPUBufferType bufferType, const void* data, int size)
{
    GPUBuffer* bufferPtr = new GPUBuffer();

    bufferPtr->bufferType = bufferType;

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    switch (bufferType) {
    case VERTEXBUFFER:
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, size * 4, data, GL_STATIC_DRAW);
        break;
    case INDEXBUFFER:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * 4, data, GL_STATIC_DRAW);
        break;
    case SHADERINPUTBUFFER:
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
        break;
    }

    bufferPtr->unbaseVars["bufferID"] = (int)buffer;

    return bufferPtr;
}

GPUMesh* GPUContext::createMesh(Vertex verticesStruct[], int verticesSize, int indices[], int indicesSize)
{
    GPUMesh* mesh = new GPUMesh();

    std::vector<float> vertices;
    for (int i = 0; i < verticesSize; i++) {
        Vertex vertex = verticesStruct[i];
        vertices.push_back(vertex.position.x);
        vertices.push_back(vertex.position.y);
        vertices.push_back(vertex.position.z);
        vertices.push_back(vertex.texCoord.x);
        vertices.push_back(vertex.texCoord.y);
        vertices.push_back(vertex.normal.x);
        vertices.push_back(vertex.normal.y);
        vertices.push_back(vertex.normal.z);
    }


    unsigned int meshLayout;
    glGenVertexArrays(1, &meshLayout);
    glBindVertexArray(meshLayout);

    mesh->vertexBuffer = this->createBuffer(VERTEXBUFFER, &vertices[0], vertices.size());
    mesh->indexBuffer = this->createBuffer(INDEXBUFFER, indices, indicesSize);

    int stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    mesh->vertexBuffer->unbind();
    mesh->indexBuffer->unbind();

    mesh->unbaseVars["meshLayout"] = (int)meshLayout;

    mesh->vertexCount = indicesSize;
    glBindVertexArray(0);
    return mesh;
}


GPURenderPass* GPUContext::createRenderPass(bool mainRenderPass, GPUFramebuffer* framebuffer, bool disallow,GPUShader* shaderToRender)
{
    GPURenderPass* renderPass = new GPURenderPass();
    if (mainRenderPass) {
        renderPass->useFramebuffer = false;
        renderPass->framebuffer = nullptr;
        renderPass->customViewport = glm::vec2(this->window->width, this->window->height);
        renderPass->disallowToRenderNotPriorityItems = disallow;
        renderPass->attachedShader = shaderToRender;
    }
    else {
        renderPass->framebuffer = framebuffer;
        renderPass->useFramebuffer = true;
        renderPass->customViewport = framebuffer->type == COLORMAP ? glm::vec2(this->window->width, this->window->height) : glm::vec2(1024, 1024);
        renderPass->disallowToRenderNotPriorityItems = disallow;
        renderPass->attachedShader = shaderToRender;
    }

    this->renderPasses.push_back(renderPass);
    return renderPass;
}

//Add colormap framebuffer
GPUFramebuffer* GPUContext::createFramebuffer(GPUFramebufferType type,bool emissionAttachment)
{
    GPUFramebuffer* framebuffer = new GPUFramebuffer();

    int width, height;
    switch (type)
    {
    case COLORMAP:
        width = this->window->width;
        height = this->window->height;
        break;
    case DEPTHMAP:
        width = 1024;
        height = 1024;
        break;
    default:
        break;
    }

    unsigned int mapFBO;
    glGenFramebuffers(1, &mapFBO);


        unsigned int map;
        glGenTextures(1, &map);
        glBindTexture(GL_TEXTURE_2D, map);
        switch (type) {
        case COLORMAP:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            break;
        case DEPTHMAP:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            break;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindTexture(GL_TEXTURE_2D, 0);

        unsigned int map2;
        if (emissionAttachment) {
            glGenTextures(1, &map2);
            glBindTexture(GL_TEXTURE_2D, map2);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor2);
            glBindTexture(GL_TEXTURE_2D, 0);
            framebuffer->unbaseVars["emissionColorBuffer"] = (int)map2;
        }



        glBindFramebuffer(GL_FRAMEBUFFER, mapFBO);

        switch (type) {
        case COLORMAP:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, map, 0);
            if (emissionAttachment) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, map2, 0);
            }
            break;
        case DEPTHMAP:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, map, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            break;
        }

        if (emissionAttachment) {
            unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 };
            glDrawBuffers(2, attachments);
        }

        framebuffer->unbaseVars["textureColorBuffer"] = (int)map;

    if (type == COLORMAP) {
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        //without multisampling:  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->window->width, this->window->height);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->window->width, this->window->height);


        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        framebuffer->unbaseVars["renderBufferObject"] = (int)rbo;
    }


    GPUFramebuffer::unbind();

    framebuffer->unbaseVars["framebufferID"] = (int)mapFBO;

    framebuffer->type = type;

    return framebuffer;
}

GPUTexture* GPUContext::createTexture(std::string filepath)
{
    GPUTexture* texture = new GPUTexture();

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    texture->unbaseVars["textureID"] = (int)texture1;

    return texture;
}

void GPUContext::createAtmosphere()
{
    this->skybox = new GPUSkybox();
    this->skybox->cubeMesh = ModelLoader::loadMesh(this, "./res/cube.obj");
}

void GPUContext::drawQueue(GPUMesh* mesh, GPUShader* shader, Transform* transform, GPUMaterial* material)
{
    GPUDrawData* drawData = new GPUDrawData();
    drawData->mesh = mesh;
    drawData->shader = shader;
    drawData->transform = transform;
    drawData->material = material;
    this->drawQueueList.push_back(drawData);
}