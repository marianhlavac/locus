//
//  Object.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//



#include "Object.hpp"

Object::Object(Mesh* mesh, vec3 position = vec3(0), string name = "Object") : mesh(mesh), name(name) {
    
}
void Object::draw() {
    mesh->draw();
}

string Object::getName() const {
    return name;
}

void Object::setName(string name) {
    this->name = name;
}
