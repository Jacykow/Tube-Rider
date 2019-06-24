#version 330

uniform sampler2D tex;
uniform vec4 ls0;
uniform vec4 ls1;
uniform float lf; //light force

in vec4 icolor;
in vec4 inormal;
in vec4 ipos;
in vec2 itexCoord;

out vec4 pixelColor;

void main(void) {
    vec4 c = texture(tex,itexCoord);
    float light0=clamp(dot(normalize(inormal),normalize(ls0-ipos)),0,1);
    float light1=clamp(dot(normalize(inormal),normalize(ls1-ipos)),0,1);
    light0 = light0*(1-clamp((distance(ipos,ls0))/lf,0,1));
    light1 = light1*(1-clamp((distance(ipos,ls1))/lf,0,1));
    c = c*0.5*(light0+light1);


    c.a = 1;
	pixelColor=c;
}

