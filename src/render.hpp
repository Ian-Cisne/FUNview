#ifndef RENDER_HPP
#define RENDER_HPP

#include "window.hpp"
#include "global.hpp"
#include "config.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Render{
    static Render* instance_; //Instancia Singleton

    Config* configuracion;
    Window* Ventana;
    uint shaderProgram;
    uint VBO, VAO, EBO;
    Render(Config*);
    
public:
    ~Render();
    Render(Render &other) = delete;
    void operator=(const Render &) = delete; //No se debe asignar ni copiar

    static Render *getInstance(Config*);
    void mainLoop();
};
void processInput(GLFWwindow *window);

#endif