//
//  Mesh.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Mesh.hpp"
#include "teapotData.cpp"

#include "Material.hpp"

Mesh::Mesh() {
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f, -0.5f, 0.0f, // Right
        0.0f,  0.5f, 0.0f  // Top
    };
    
    vao = new MeshVAO();
    vao->bind();
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

void Mesh::draw() {
    vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
