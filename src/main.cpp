/*

    Un simple graficador de polinomios


    -Ian Cisneros

*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "global.hpp"
#include "render.hpp"
#include "config.hpp"
#include "exception.hpp"

int main(const int argc, const char **argv)
{      
    try {
        Config* config = Config::getInstance(argc, argv);
        if(!config->cerrar){
            Render* render = Render::getInstance(config);
            render->mainLoop();
            delete render;
        }
        delete config;
        
    }catch(myException& e){
        std::cerr << e.what();
    }

    std::cout << std::endl;
    return 0;
}
