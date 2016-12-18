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

Mesh* Mesh::createCube(float size) {
    size *= 0.5f;
    
    vector<GLfloat> buffer = {
        -size, size, -size,
        -size, size, size,
        -size, -size, -size,
        -size, -size, size,
        size, size, -size,
        size, size, size,
        size, -size, -size,
        size, -size, size
    };
    
    vector<GLuint> indices = {
        1, 4, 0,
        1, 5, 4,
        2, 6, 3,
        6, 7, 3,
        3, 5, 1,
        7, 5, 3,
        4, 5, 7,
        6, 4, 7,
        2, 4, 6,
        0, 4, 2,
        1, 0, 2,
        2, 3, 1
    };
    
    Mesh* mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 3, GL_FLOAT, 3, 0);
    return mesh;
}

Mesh* Mesh::createICube(float size) {
    size *= 0.5f;
    
    vector<GLfloat> buffer = {
        -size, size, -size,
        -size, size, size,
        -size, -size, -size,
        -size, -size, size,
        size, size, -size,
        size, size, size,
        size, -size, -size,
        size, -size, size
    };
    
    vector<GLuint> indices = {
        0, 4, 1,
        4, 5, 1,
        3, 6, 2,
        3, 7, 6,
        1, 5, 3,
        3, 5, 7,
        7, 5, 4,
        7, 4, 6,
        6, 4, 2,
        2, 4, 0,
        2, 0, 1,
        1, 3, 2
    };
    
    Mesh* mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 3, GL_FLOAT, 3, 0);
    return mesh;
}

Mesh* Mesh::createQuad(vec2 size) {
    size *= 0.5f;
    
    vector<GLfloat> buffer = {
        size.x, 0, size.y, 1, 0,
        size.x, 0, -size.y, 1, 1,
        -size.x, 0, size.y, 0, 0,
        -size.x, 0, -size.y, 0, 1
    };
    
    vector<GLuint> indices = {
        3, 2, 1,
        1, 2, 0
    };
    
    Mesh* mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 3, GL_FLOAT, 5, 0);
    mesh->addAttrib(2, 2, GL_FLOAT, 5, 3);
    return mesh;
}
