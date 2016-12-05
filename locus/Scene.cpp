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
    this->isDrawable = false;
}

Camera* Scene::getAttachedCamera() {
    return camera;
}

void Scene::attachCamera(Camera *camera) {
    this->camera = camera;
}

void Scene::draw() {
    for (Child* obj : children) {
        if (obj->isDrawable) ((Object*)obj)->draw();
    }
}

void Scene::addMaterial(Material* material) {
    materials.push_back(material);
}

void Scene::addDirectionalLight(DirectionalLight* light) {
    directionalLights.push_back(light);
    children.push_back(light);
}

void Scene::addPointLight(PointLight* light) {
    pointLights.push_back(light);
    children.push_back(light);
}

void Scene::addSpotLight(SpotLight* light) {
    spotLights.push_back(light);
    children.push_back(light);
}

void Scene::updateMaterials() {
    for (Material* mat : materials) {
        Shader* shader = mat->getShader();
        
        shader->setLightsCount((GLuint)directionalLights.size(), (GLuint)pointLights.size(), (GLuint)spotLights.size());
        
        int i = 0;
        for (DirectionalLight* light : directionalLights) {
            shader->setUniform("directionalLights", i, "direction", light->getPosition());
            shader->setADS("directionalLights", i, mat->ambient, mat->diffuse, mat->specular);
            i++;
        }
        
        i = 0;
        for (PointLight* light : pointLights) {
            shader->setUniform("pointLights", i, "position", light->getPosition());
            shader->setUniform("pointLights", i, "constant", light->getConstant());
            shader->setUniform("pointLights", i, "linear", light->getLinear());
            shader->setUniform("pointLights", i, "quadratic", light->getQuadratic());
            shader->setADS("pointLights", i, mat->ambient, mat->diffuse, mat->specular);
            i++;
        }
        
        
        mat4 view = ((Camera*)camera)->getViewMatrix();
        mat4 projection = ((Camera*)camera)->getProjectionMatrix();
        mat->updateVP(view, projection);
    }
}
