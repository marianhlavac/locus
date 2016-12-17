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
#include "Camera.hpp"

Material* noMaterial = nullptr;

Object::Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale, Material* mat) : mesh(mesh), position(position), rotation(fquat(rotation)), scale(scale), material(mat) {
    this->name = name;
    this->isDrawable = true;
    this->selectionId = -1;
}

Object::Object(Mesh* mesh, string name, vec3 position, vec3 rotation, Material* mat) : mesh(mesh), position(position), rotation(fquat(rotation)), scale(vec3(1)), material(mat) {
    this->name = name;
    this->isDrawable = true;
    this->selectionId = -1;
}

Object::Object(Mesh* mesh, string name, vec3 position, Material* mat) : mesh(mesh), position(position), rotation(vec3(0)), scale(vec3(1)), material(mat) {
    this->name = name;
    this->isDrawable = true;
    this->selectionId = -1;
}

Object::Object(string name, vec3 position, vec3 rotation, vec3 scale) : mesh(nullptr), position(position), rotation(fquat(rotation)), scale(scale) {
    this->name = name;
    this->isDrawable = false;
    this->selectionId = -1;
}

Object::Object(string name, vec3 position, vec3 rotation) : mesh(nullptr), position(position), rotation(fquat(rotation)), scale(vec3(1)) {
    this->name = name;
    this->isDrawable = false;
    this->selectionId = -1;
}

Object::Object(string name, vec3 position) : mesh(nullptr), position(position), scale(vec3(1)) {
    this->name = name;
    this->isDrawable = false;
    this->selectionId = -1;
}

void Object::draw() {
    draw(this);
}

void Object::draw(Object* parent) {
    draw(parent, noMaterial);
}

void Object::draw(Material* forcedMaterial) {
    draw(this, forcedMaterial);
}

void Object::draw(Object* parent, Material* forcedMaterial) {
    mat4 model;
    
    if (parent != this) {
        model = parent->getTransformationMatrix() * getTransformationMatrix();
    } else {
        model = getTransformationMatrix();
    }
    
    if (forcedMaterial == noMaterial) {
        material->use();
        material->updateM(model);
        if (selectionId >= 0) {
            material->getShader()->setUniform("selectionId", (GLuint)selectionId);
        }
    } else {
        forcedMaterial->use();
        forcedMaterial->updateM(model);
        if (selectionId >= 0) {
            forcedMaterial->getShader()->setUniform("selectionId", (GLuint)selectionId);
        }
    }
    
    
    mesh->draw();
    
    if (forcedMaterial == noMaterial) {
        if (selectionId >= 0) {
            material->getShader()->setUniform("selectionId", (GLuint)0);
        }
    } else {
        if (selectionId >= 0) {
            forcedMaterial->getShader()->setUniform("selectionId", (GLuint)0);
        }
    }
    
    // Draw all children
    for (Child* child : children) {
        if (child->isDrawable) ((Object*) child)->draw(this, forcedMaterial); else ((Object*) child)->traverse(this, forcedMaterial);
    }
}

void Object::traverse(Object* parent) {
    traverse(parent, noMaterial);
}

void Object::traverse(Object* parent, Material* forcedMaterial) {
    mat4 model;
    
    if (parent != this) {
        model = parent->getTransformationMatrix() * getTransformationMatrix();
    } else {
        model = getTransformationMatrix();
    }
    
    // Draw all children
    for (Child* child : children) {
        if (child->isDrawable) ((Object*) child)->draw(this, forcedMaterial); else ((Object*) child)->traverse(this, forcedMaterial);
    }
}

vec3 Object::getPosition() {
    return position;
}

fquat Object::getRotation() {
    return rotation;
}

vec3 Object::getRotation(vec3 target) {
    return rotation * target;
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

void Object::setSelectionId(int selectionId) {
    this->selectionId = selectionId;
}

int Object::getSelectionId() {
    return selectionId;
}
