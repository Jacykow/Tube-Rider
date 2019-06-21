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
    std::string name;
    glm::mat4 M;
    Models::Model* model;
    ShaderProgram* shaderProgram;
    void draw();
};

#endif
