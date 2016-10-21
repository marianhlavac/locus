//
//  Scene.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Scene.hpp"

using namespace std;

Scene::Scene(string name) : name(name), camera(nullptr) {
    
}

string Scene::getName() {
    return name;
}

list<Object*> Scene::getChildren() {
    return children;
}

Object* Scene::getChildByName(string childName) {
    auto it = find_if(children.begin(), children.end(), [&] (Object* const &p) { return p->getName() == childName; });
    
    if (it == children.end()) {
        throw runtime_error("There is no children named '" + childName + "' in scene '" + name + "'.");
    }
    
    return *it;
}

void Scene::addChild(Object* child) {
    children.push_back(child);
}

void Scene::removeChild(Object* child) {
    children.remove(child);
}

void Scene::removeChildByName(string childName) {
    removeChild(getChildByName(childName));
}

void Scene::attachCamera(Camera *camera) {
    this->camera = camera;
}

Camera* Scene::getAttachedCamera() {
    return camera;
}

void Scene::draw() {
    if (camera == nullptr) {
        throw runtime_error("No camera attached to scene");
    }
    
    mat4 viewProjectionMatrix = camera->getProjectionMatrix() * camera->getViewMatrix();
    
    for (Object* obj : children) {
        obj->draw(viewProjectionMatrix);
    }
}
