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

Mesh::Mesh(WavefrontParserResult* parsed) : Mesh(parsed->flatBuffer, (GLuint)parsed->flatBuffer.size(), parsed->indices, (GLuint)parsed->indices.size()) {
    vao->bind();
    verticesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);
    verticesVbo->addAttrib(0, 3, GL_FLOAT, 8, 0);
    verticesVbo->addAttrib(1, 3, GL_FLOAT, 8, 3);
    verticesVbo->addAttrib(2, 2, GL_FLOAT, 8, 6);
    vao->unbind();
}

Mesh::Mesh(vector<GLfloat> buffer, GLuint bufferSize, vector<GLuint> indices, GLuint indicesSize) {
    vao = new MeshVAO();
    vao->bind();
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, &buffer[0], bufferSize * sizeof(GLfloat), GL_STATIC_DRAW);
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, &indices[0], indicesSize * sizeof(GLuint), GL_STATIC_DRAW);
    
    vao->unbind();
    
    vertexCount = indicesSize;
    triangleCount = indicesSize / 3;
}

void Mesh::draw() {
    vao->bind();
    indicesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexCount, GL_UNSIGNED_INT, (void*)0);
    vao->unbind();
}

void Mesh::addAttrib(GLuint location, GLint size, GLenum type, GLsizei stride, int start) {
    vao->bind();
    verticesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);
    verticesVbo->addAttrib(location, size, type, stride, start);
    vao->unbind();
}
