#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "allmodels.h"
#include "shaderprogram.h"

class gameObject{
public:
    glm::mat4 drawM;
    Models::Model* model;
    ShaderProgram* shaderProgram;
    void draw();
};

class obstacle : public gameObject{
public:
    float z; // distance to ship
    int orderInRow;
};

#endif
