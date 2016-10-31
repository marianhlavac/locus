//
//  Mesh.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <iostream>

#include "Mesh.hpp"
using namespace std;

Mesh::Mesh(WavefrontParserResult* parsed, Material* mat) : material(mat) {
    vao = new MeshVAO();
    vao->bind();
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, &parsed->vertices[0], parsed->vertices.size() * sizeof(GLfloat));
    verticesVbo->addAttrib(mat->getAttribLocation("position"), 3, GL_FLOAT, 0, (void*)0);
    
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, &parsed->vertexIndices[0], parsed->vertexIndices.size() * sizeof(GLuint));
    
    vao->unbind();
    
    vertexCount = parsed->vertices.size() / 3;
    triangleCount = parsed->vertexIndices.size() / 3;
}

void Mesh::draw(mat4 transform) {
    material->use();
    material->setUniformMf4("mvp", transform);
    vao->bind();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLES, (GLsizei)triangleCount * 3, GL_UNSIGNED_INT, (void*)0);
}
