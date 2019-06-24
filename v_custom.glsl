
#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 color;

//Atrybuty
layout (location=0) in vec4 vertex;
layout (location=1) in vec4 normal;
layout (location=2) in vec2 texCoord;

out vec4 icolor;
out vec4 inormal;
out vec2 itexCoord;
out vec4 ipos;

void main(void) {
    gl_Position=P*V*M*vertex;
    icolor = color;
    ipos = M*vertex;
    inormal = M*normal;
    itexCoord=texCoord;
}
