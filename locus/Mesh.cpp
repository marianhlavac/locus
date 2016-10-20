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

Mesh::Mesh(vector<GLfloat> vertices, vector<GLuint> indices, Material* mat) : material(mat) {
    vao = new MeshVAO();
    vao->bind();
    
    verticesVbo = new MeshVBO(GL_ARRAY_BUFFER, &vertices[0], vertices.size() * sizeof(GLfloat));
    verticesVbo->addAttrib(mat->getAttribLocation("position"), 3, GL_FLOAT, 0, (void*)0);
    
    indicesVbo = new MeshVBO(GL_ELEMENT_ARRAY_BUFFER, &indices[0], indices.size() * sizeof(GLuint));
    
    vao->unbind();
    
    vertexCount = vertices.size() / 3;
    triangleCount = indices.size() / 3;
}

void Mesh::draw(mat4 transform) {
    material->use();
    material->setUniformMf4("mvp", transform);
    vao->bind();
    glDrawElements(GL_LINES, triangleCount * 3, GL_UNSIGNED_INT, (void*)0);
}

Mesh* Mesh::loadFromFile(const string & filename, Material* material) {
    vector<GLfloat> vertices;
    vector<GLuint> indices;
    
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        
        string type;
        float x, y, z;
        int vtx1, vtx2, vtx3;
        
        ss >> type;
        
        if (type == "v") {
            ss >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
        
        if (type == "f") {
            string s1, s2, s3;
            ss >> s1 >> s2 >> s3;
            
            stringstream ss1(s1), ss2(s2), ss3(s3);
            
            ss1 >> vtx1;
            ss2 >> vtx2;
            ss3 >> vtx3;
            
            indices.push_back(vtx1);
            indices.push_back(vtx2);
            indices.push_back(vtx3);
        }
    }
    
    return new Mesh(vertices, indices, material);
}
