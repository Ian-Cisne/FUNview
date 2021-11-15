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
uniform uint u_Grado;
uniform bool u_Guias;


void main()
{  
    if(!u_Guias){
        float xPos = (aPos-u_Resolution.x)/u_Resolution.x; 
        float ratio =  u_Resolution.x/u_Resolution.y;
        float cX = xPos * (10*ratio/u_Zoom);

        float res = 0;
        int grado = int(u_Grado);
    
        for(int i = grado; i >= 0; i--){
            float aux = 1;
            
            for(int j = 0; j < grado-i; j++){aux = aux * cX;}
                
            res = res + aux * u_Coeficientes[i];
        }

        float yPos = res/(10/u_Zoom);


        gl_Position = vec4(xPos, yPos, 0.0, 1.0);
    }
    else{
        if(aPos == 1.0)
            gl_Position = vec4( 1.0,  0.0, 0.0, 1.0);
        else if(aPos == 2.0)
            gl_Position = vec4(-1.0,  0.0, 0.0, 1.0);
        else if(aPos == 3.0)
            gl_Position = vec4( 0.0,  1.0, 0.0, 1.0);
        else if(aPos == 4.0)
            gl_Position = vec4( 0.0, -1.0, 0.0, 1.0);
    }
}
)";