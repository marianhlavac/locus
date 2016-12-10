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

Mesh::Mesh(WavefrontParserResult* parsed){
    vao = new MeshVAO();
    vao->bind();
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, &parsed->flatBuffer[0], parsed->flatBuffer.size() * sizeof(GLfloat), GL_STATIC_DRAW);
    verticesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);
    verticesVbo->addAttrib(0, 3, GL_FLOAT, 8, 0);
    verticesVbo->addAttrib(1, 3, GL_FLOAT, 8, 3);
    verticesVbo->addAttrib(2, 2, GL_FLOAT, 8, 6);
    
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, &parsed->indices[0], parsed->indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
    
    vao->unbind();
    
    vertexCount = parsed->indices.size();
    triangleCount = parsed->indices.size() / 3;
}

void Mesh::draw() {
    vao->bind();
    indicesVbo->bind(GL_ELEMENT_ARRAY_BUFFER);    
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexCount, GL_UNSIGNED_INT, (void*)0);
}
