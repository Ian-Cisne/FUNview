#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.hpp"
#include "global.hpp"
#include "config.hpp"
#include "exception.hpp"

Render* Render::instance_ = 0;

Render* Render::getInstance(Config* a) {

    if (!instance_)
        instance_ = new Render(a);
    return instance_;
}

Render::~Render(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

uint getVertShader(){
    uint vertShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    char infoLog[512];
    int success;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cout << "Fallo la compilacion del shader de vertices\n" << infoLog << std::endl;
    }
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    return vertShader;
}

uint getFragShader(){
    int success;
    uint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    char infoLog[512];
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "Fallo la compilacion del shader de fragmentos\n" << infoLog << std::endl;
    }
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    
    return fragShader;
}

Render::Render(Config* config): configuracion(config) {

    this->Ventana = new Window(configuracion->anchoPantalla, configuracion->altoPantalla);
    int success;
    char infoLog[512];

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "No se pudo incializar GLAD" << std::endl;
    }

    uint vertShader = getVertShader();
    uint fragShader = getFragShader();

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram (shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        std::wcout << "Falló el linkeo de shaders al program shader\n" << infoLog << std::endl;
    }/*
    GLint count;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
    for (int i = 0; i < count; i++) {
        char name[100];
        glGetActiveUniformName(shaderProgram, i, sizeof(name), (GLsizei*) NULL, name);
        std::cout << name << "\n";
    }
*/


    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(VAO);

    std::vector <float> _vertices(configuracion->anchoPantalla);
    std::vector <uint> _indices(configuracion->anchoPantalla*2);
    for(uint i=0; i<configuracion->anchoPantalla; i++) _vertices[i]= i;
    for(uint i=0; i<configuracion->anchoPantalla*2; i=i+2) {_indices[i]= (i+1)/2;_indices[i+1]= (i+2)/2; }

    float *__vertices = &_vertices[0];
    uint *__indices = &_indices[0];

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(float), __vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint), __indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

}

void Render::mainLoop(){

    configuracion->coeficientes[0] = 2;
    configuracion->coeficientes[1] = 3;
    configuracion->coeficientes[2] = 6;

    std::cout << "Coeficientes:\n";

    for(int i = 0; i <= configuracion->grado; i++){
        std::cout << "X^" << configuracion->grado-i << ": " << configuracion->coeficientes[i] <<", Índice: "<< i << "\n";
    }

    std::cout << "Grado: " << configuracion->grado << std::endl;
    while(Ventana->shouldClose()){
        Ventana->processInput();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int u_resolution = glGetUniformLocation(shaderProgram, "u_Resolution");
        glUniform2f(u_resolution, configuracion->anchoPantalla/2, configuracion->altoPantalla/2);

        int u_color = glGetUniformLocation(shaderProgram, "u_Color");
        glUniform3f(u_color, 1.0f, 0.0f, 0.0f);

        int u_zoom = glGetUniformLocation(shaderProgram, "u_Zoom");
        glUniform1f(u_zoom, configuracion->zoom);

        int u_coeficientes = glGetUniformLocation(shaderProgram, "u_Coeficientes");
        glUniform1fv(u_coeficientes, MAX_GRADO, &configuracion->coeficientes[0]);

        int u_grado = glGetUniformLocation(shaderProgram, "u_Grado");
        glUniform1ui(u_grado, int(configuracion->grado));

        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, configuracion->anchoPantalla, GL_UNSIGNED_INT,0);
 
        Ventana->actualizeState();
    }

}
