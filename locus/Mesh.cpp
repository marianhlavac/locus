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
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, &parsed->flatBuffer[0], parsed->flatBuffer.size() * sizeof(GLfloat));
    verticesVbo->addAttrib(mat->getAttribLocation("position"), 3, GL_FLOAT, 8, 0);
    verticesVbo->addAttrib(mat->getAttribLocation("normal"), 3, GL_FLOAT, 8, 3);
    verticesVbo->addAttrib(mat->getAttribLocation("uv"), 2, GL_FLOAT, 8, 6);
    
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, &parsed->indices[0], parsed->indices.size() * sizeof(GLuint));
    
    vao->unbind();
    
    vertexCount = parsed->indices.size();
    triangleCount = parsed->indices.size() / 3;
}

void Mesh::draw(mat4 modelTransform, mat4 viewTransform, mat4 projectionTransform, vec3 viewPos) {
    material->use();
    
    material->setUniform("mvp", projectionTransform * viewTransform * modelTransform);
    material->setUniform("m", modelTransform);
    material->setUniform("v", viewTransform);
    material->setUniform("lightPos", vec3(0, -1, 0));
    material->setUniform("viewPos", viewPos);
    
    vao->bind();
    indicesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexCount, GL_UNSIGNED_INT, (void*)0);
}
