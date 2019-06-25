
#include "gameObject.h"

void gameObject::draw(ShaderProgram* shader){
    glUniformMatrix4fv(shader->u("M"),1,false,glm::value_ptr(drawM));
    glUniform4f(shader->u("color"),color.x,color.y,color.z,color.w);

    glUniform1i(shader->u("tex"),0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    model->drawSolid(smooth);
}
