//
//  Object.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Object.hpp"

Object::Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale) : mesh(mesh), name(name), position(position), rotation(rotation), scale(scale) {
    
}

Object::Object(string name, vec3 position, vec3 rotation, vec3 scale) : mesh(nullptr), name(name), position(position), rotation(rotation), scale(scale) {
    
}

void Object::draw(mat4 viewTransformationMatrix) {
    mesh->draw(viewTransformationMatrix * getTransformationMatrix());
}

string Object::getName() const {
    return name;
}

void Object::setName(string name) {
    this->name = name;
}

vec3 Object::getPosition() {
    return position;
}

vec3 Object::getRotation() {
    return rotation;
}

vec3 Object::getScale() {
    return scale;
}

void Object::setPosition(vec3 position) {
    position = position;
}

void Object::setRotation(vec3 rotation) {
    rotation = rotation;
}

void Object::setScale(vec3 scale) {
    scale = scale;
}

mat4 Object::getTransformationMatrix() {
    return translate(position) * orientate4(rotation) * glm::scale(scale);
}
