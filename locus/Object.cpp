//
//  Object.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <OpenGL/gl3.h>

#include "Object.hpp"

Object::Object(Mesh* mesh, Material* material, sf::Vector3f position = sf::Vector3f(0,0,0), string name = "Object") : mesh(mesh), material(material), name(name) {
    
}

Material* Object::getMaterial() {
    return material;
}

void Object::draw() {
    material->use();
    mesh->draw();
}

string Object::getName() const {
    return name;
}

void Object::setName(string name) {
    this->name = name;
}
