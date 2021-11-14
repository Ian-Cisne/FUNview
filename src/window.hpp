#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "global.hpp"

class Window {
private:
    GLFWwindow *windowHandler;
    friend class Render;
public:
    Window(uint width, uint height);
    bool shouldClose(){ return !glfwWindowShouldClose(windowHandler); }
    void processInput();
    void actualizeState();

};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
