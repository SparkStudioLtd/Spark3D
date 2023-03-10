#include "CoreFramework.h"



void GPUWindow::createWindow(std::string title, int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        //Debug::error("Failed to create window");
        glfwTerminate();
    }

    this->unbaseVars["windowHandle"] = Obj(window);

    this->width = width;
    this->height = height;
    this->title = title;
}