//
//  Scene.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Scene.hpp"

using namespace std;

Scene::Scene(string name) : camera(nullptr) {
    this->name = name;
}

Camera* Scene::getAttachedCamera() {
    return camera;
}

void Scene::attachCamera(Camera *camera) {
    this->camera = camera;
}

void Scene::draw() {
    if (camera == nullptr) {
        throw runtime_error("No camera attached to scene");
    }
    
    for (Child* obj : children) {
        ((Object*)obj)->draw(camera->getViewMatrix(), camera->getProjectionMatrix());
    }
}
