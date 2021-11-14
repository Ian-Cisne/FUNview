#include "global.hpp"

extern char* fragSource =
R"(#version 330 core
out vec4 FragColor;
in vec4 gl_FragCoord;

uniform vec3 u_Color;

void main()
{
    FragColor = vec4(u_Color, 1.0);
}
)";
extern char* vertSource = 
R"(#version 330 core
layout (location = 0) in float aPos;

uniform vec2 u_Resolution;
uniform float u_Zoom;
uniform float u_Coeficientes[16];
uniform int u_Grado;

void main()
{  
    float xPos = (aPos-u_Resolution.x)/u_Resolution.x; 
    float cX = xPos * (20/u_Zoom);

    float res = 0;
    int b = u_Grado+1;
    int a = b-1;
    int c = b-2;

    res =  cX*cX*u_Coeficientes[0];
    res +=  cX*u_Coeficientes[1];
    res += u_Coeficientes[u_Grado+2];

    //res = cX*cX*u_Coeficientes[0]+cX*u_Coeficientes[1]+u_Coeficientes[2];
    //res = cX*cX*u_Coeficientes[grado-2]+cX*u_Coeficientes[grado-1]+u_Coeficientes[grado-0]; grado: 2

    //res = cX*cX*cX*u_Coeficientes[0]+cX*cX*u_Coeficientes[1]+cX*u_Coeficientes[2]+u_Coeficientes[3];
    //res = cX*cX*cX*u_Coeficientes[0]+cX*cX*u_Coeficientes[1]+cX*u_Coeficientes[2]+u_Coeficientes[3];

    /*
    for(int i = u_Grado; i >= 0; i--){
        float aux = 1;
        
        for(int j = 0; j < u_Grado-i; j++){aux = aux * cX;}
            
        res = res + aux * u_Coeficientes[i];
    }*/

    float yPos = res/(10/u_Zoom);


    gl_Position = vec4(xPos, yPos, 0.0, 1.0);
}
)";