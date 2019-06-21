
#include "gameObject.h"

void gameObject::draw(){
    glUniformMatrix4fv(shaderProgram->u("M"),1,false,glm::value_ptr(drawM));
    glUniform4f(spLambert->u("color"),color.x,color.y,color.z,color.w);
    model->drawSolid(true);
}
