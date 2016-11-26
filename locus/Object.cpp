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

Object::Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale) : mesh(mesh), position(position), rotation(fquat(rotation)), scale(scale) {
    this->name = name;
}

Object::Object(Mesh* mesh, string name, vec3 position, vec3 rotation) : mesh(mesh), position(position), rotation(fquat(rotation)), scale(vec3(1)) {
    this->name = name;
}

Object::Object(Mesh* mesh, string name, vec3 position) : mesh(mesh), position(position), scale(vec3(1)) {
    this->name = name;
}

Object::Object(string name, vec3 position, vec3 rotation, vec3 scale) : mesh(nullptr), position(position), rotation(fquat(rotation)), scale(scale) {
    this->name = name;
}

Object::Object(string name, vec3 position, vec3 rotation) : mesh(nullptr), position(position), rotation(fquat(rotation)), scale(vec3(1)) {
    this->name = name;
}

Object::Object(string name, vec3 position) : mesh(nullptr), position(position), scale(vec3(1)) {
    this->name = name;
}

void Object::draw(mat4 viewTransform, mat4 projectionTransform) {
    mesh->draw(getTransformationMatrix(), viewTransform, projectionTransform);
}

vec3 Object::getPosition() {
    return position;
}

fquat Object::getRotation() {
    return rotation;
}

vec3 Object::getScale() {
    return scale;
}

void Object::setPosition(vec3 position) {
    this->position = position;
}

void Object::setRotation(fquat rotation) {
    this->rotation = rotation;
}

void Object::setRotation(vec3 eulerAngles) {
    this->rotation = quat(eulerAngles);
}

void Object::setScale(vec3 scale) {
    this->scale = scale;
}

mat4 Object::getTransformationMatrix() {
    return translate(position) * toMat4(rotation) * glm::scale(scale);
}

void Object::rotateBy(vec3 eulerAngles) {
    this->rotation *= quat(eulerAngles);
}
