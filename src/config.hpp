#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "global.hpp"

#include <vector>

class Config{
private:
    static Config* instance_;
    
    Config(const int argc, const char **argv);
public:
    ~Config();
    uint anchoPantalla;
    uint altoPantalla;
    float zoom;
    uint grado;
    std::vector<float> coeficientes;
    bool cerrar;

    Config(Config &other) = delete;
    void operator=(const Config &) = delete; //No se debe asignar ni copiar

    static Config* getInstance(const int argc, const char **argv);
};

#endif