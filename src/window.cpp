#include "window.hpp"

#include <iostream>

Window::Window(uint width, uint height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    windowHandler = glfwCreateWindow(width, height, "FUNview", NULL, NULL);
    if (windowHandler == NULL)
    {
        std::cout << "No se pudo incializar una ventana de GLFW" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(windowHandler);
    glfwSetFramebufferSizeCallback(windowHandler, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::processInput()
{
    if (glfwGetKey(windowHandler, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(windowHandler, true);
}
void Window::actualizeState(){
    glfwSwapBuffers(windowHandler);
    glfwPollEvents();
}