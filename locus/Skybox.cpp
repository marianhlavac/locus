//
//  Skybox.cpp
//  locus
//
//  Created by Marián Hlaváč on 17/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Skybox.hpp"

Skybox::Skybox(float size, Material* material) : material(material) {
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
    
    mesh = new Mesh(buffer, (GLuint)buffer.size(), indices, (GLuint)indices.size());
    mesh->addAttrib(0, 3, GL_FLOAT, 3, 0);
}

void Skybox::draw() {
    glDepthMask(GL_FALSE);
    material->use();
    material->updateM(mat4(1));
    mesh->draw();
    glDepthMask(GL_TRUE);
}
