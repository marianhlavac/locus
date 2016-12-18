//
//  Graphic2D.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Graphic2D.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

Graphic2D::Graphic2D(Material* material, vec2 position, vec2 size) : material(material), position(position), size(size) {
    
    vector<GLfloat> buffer = {
        position.x, position.y, 0, 1,
        position.x + size.x, position.y, 1, 1,
        position.x, position.y + size.y, 0, 0,
        position.x + size.x, position.y + size.y, 1, 0
    };
    
    vector<GLuint> indices = {
        0, 1, 2,
        2, 1, 3
    };
    
    mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 4, GL_FLOAT, 4, 0);
}

void Graphic2D::draw() {
    draw(vec4(0, 1280.0f, 0, 720.0f));
}

void Graphic2D::draw(vec4 proj) {
    glDisable(GL_DEPTH_TEST);
    material->use();
    
    mat4 projection = glm::ortho(proj.x, proj.y, proj.z, proj.w);
    material->getShader()->setUniform("mvp", projection);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mesh->draw();
    glEnable(GL_DEPTH_TEST);
}

void Graphic2D::setSize(vec2 size) {
    this->size = size;
    
    delete mesh;
    
    vector<GLfloat> buffer = {
        position.x, position.y, 0, 1,
        position.x + size.x, position.y, 1, 1,
        position.x, position.y + size.y, 0, 0,
        position.x + size.x, position.y + size.y, 1, 0
    };
    
    vector<GLuint> indices = {
        0, 1, 2,
        2, 1, 3
    };
    
    mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 4, GL_FLOAT, 4, 0);
}
