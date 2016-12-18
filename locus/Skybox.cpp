//
//  Skybox.cpp
//  locus
//
//  Created by Marián Hlaváč on 17/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Skybox.hpp"

Skybox::Skybox(float size, Material* material) : material(material) {
    mesh = Mesh::createICube(size);
}

void Skybox::draw() {
    glDepthMask(GL_FALSE);
    material->use();
    material->updateM(mat4(1));
    mesh->draw();
    glDepthMask(GL_TRUE);
}
