#include "config.hpp"
#include "exception.hpp"


#include <string>
#include <string.h>
#include <iostream>

struct par{
    std::string opcion;
    bool usado;
};

std::string textoAyuda = R"(
    ----FUNview----

Graficador de polinomios

-h --help       Muestra una breve descripción de los comandos
-px <X>         Ingresa el ancho de la pantalla en X píxeles (800 por defecto)
-py <Y>         Ingresa el alto de la pantalla en Y píxeles (600)
-z <I>          Ingresa el nivel de zoom del gráfico (1)
-g <G>          Ingresa el grado de la función (1), debe especificarse antes de -c
-c [A1 A2 A3...]Ingresa los coeficientes del polinomio que deberán ser 1 más que el grado

Ejemplo de uso:

    FUNview -px 500 -py 500 -g 3 -c 2 4 1 2

Esa ejecución resultaría en el gráfico de la función

    p(x) =  2*x³ + 4*x² + x + 2,

en una pantalla de 500x500 píxeles.

(c) Ian Cisneros, 2021
)";


Config* Config::instance_ = 0;

Config* Config::getInstance(const int argc, const char **argv){
    if(!instance_)
        instance_ = new Config(argc, argv);

    return instance_;
}

Config::Config(const int argc, const char **argv):
    anchoPantalla(1000),
    altoPantalla(500),
    zoom(1.0),
    grado(2),
    cerrar(false)
{
    std::vector<bool> opcionesUsadas(5, false);
    
    coeficientes.resize(MAX_GRADO);

    for(unsigned short i=1; i < argc; ++i){
        
        if(0 == strcmp(argv[i],"-px")){
            if(!opcionesUsadas[0]){
                opcionesUsadas[0]=true;
                if(i==argc-1)
                    throw myException((char*)"Usando -px pero no especificando ancho");
                
                anchoPantalla= std::stoul(std::string(argv[++i]));
            }else{
                throw myException((char*)"Opcion -px usada dos veces");
            }
        }else if(0 == strcmp(argv[i],"-py")){
            if(!opcionesUsadas[1]){
                opcionesUsadas[1]=true;
                if(i==argc-1)
                    throw myException((char*)"Usando -py pero no especificando ancho");
                
                altoPantalla= std::stoul(std::string(argv[++i]));
            }else{
                throw myException((char*)"Opcion -py usada dos veces");
            }    
        }else if(0 == strcmp(argv[i],"-z")){
            if(!opcionesUsadas[2]){
                opcionesUsadas[2]=true;
                if(i==argc-1)
                    throw myException((char*)"Usando -py pero no especificando ancho");
                
                zoom = std::stof(std::string(argv[++i]));
            }else{
                throw myException((char*)"Opcion -z usada dos veces");
            }    
        }else if(0 == strcmp(argv[i],"-g")){
            if(!opcionesUsadas[3]){
                opcionesUsadas[3]=true;
                if(i==argc-1)
                    throw myException((char*)"Usando -g pero no especificando grado");
                i++;
                if(opcionesUsadas[4])
                    throw myException((char*)"-c especificado antes");
                grado = std::stoul(std::string(argv[i]));
                if(grado > MAX_GRADO)
                    throw myException((char*)"El grado máximo es de 16");
            }else{
                throw myException((char*)"Opcion -g usada dos veces");
            }    
        }else if(0 == strcmp(argv[i],"-c")){
            if(!opcionesUsadas[4]){
                opcionesUsadas[4]=true;
                for(uint j=1; j <= grado+1; ++j){
                    i++;
                    coeficientes[j-1]= std::stof(std::string(argv[i]));
                }
            }else{
                throw myException((char*)"Opcion -c usada dos veces");
            }    
        }else if(0 == strcmp(argv[i],"-h") || 0 == strcmp(argv[i],"--help")){
            
            throw myException((char*)textoAyuda.c_str());
            cerrar = true;  
        }else{
            throw myException((char*)"Comando desconocido");
        }
    }

    

}
Config::~Config(){
    //for(uint i=0;i<=grado;++i) std::cout << coeficientes[grado] << " ";
}