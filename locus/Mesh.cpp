//
//  Mesh.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Mesh.hpp"
#include "teapotData.cpp"

Mesh::Mesh(Material* mat) : material(mat) {
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        0.0f,  -1.0f, 0.0f
    };
    
    GLuint indices[] = {
        0, 1, 2,
        0, 1, 3
    };
    
    vao = new MeshVAO();
    vao->bind();
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    verticesVbo->addAttrib(mat->getAttribLocation("position"), 3, GL_FLOAT, 0, (void*)0);
    
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
    
    vao->unbind();
}

void Mesh::draw() {
    material->use();
    vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}
