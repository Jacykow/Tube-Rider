
#include "gameObject.h"

void gameObject::draw(){
    glUniformMatrix4fv(shaderProgram->u("M"),1,false,glm::value_ptr(drawM));
    model->drawSolid(true);
}
