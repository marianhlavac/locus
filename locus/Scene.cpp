//
//  Scene.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Scene.hpp"

#include <fstream>
#include <iostream>
#include <map>

#include <json/json.h>
#include "ResourcePath.hpp"
#include "FreeCamera.hpp"

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

Scene* Scene::fromFile(const string &filename) {
    ifstream file(filename);
    Json::Value root;
    map<string, Mesh*> meshes;
    map<string, Material*> materials;
    
    // Read JSON
    file >> root;
    
    // Create scene
    Scene* scene = new Scene(root.get("name", "Scene Name").asString());
    string attachedCamera = root.get("camera", "none").asString();
    
    // Create meshes
    for (string meshName : root["meshes"].getMemberNames()) {
        string filename = root["meshes"].get(meshName, "Mesh").asString();
        
        WavefrontParserResult* parsedObj = WavefrontParser::parse(resourcePath() + filename);
        Mesh* mesh = new Mesh(parsedObj);
        
        meshes.insert(make_pair(meshName, mesh));
    }
    
    // Create materials
    for (string matName : root["materials"].getMemberNames()) {
        string filename = root["materials"].get(matName, "Material").asString();
        
        Material* material = Material::fromFile(resourcePath() + filename);
        
        materials.insert(make_pair(matName, material));
        scene->addMaterial(material);
    }
    
    // Create objects
    for (Json::Value object : root["objects"]) {
        Mesh* mesh = meshes[object.get("mesh", "").asString()];
        Material* mat = materials[object.get("material", "").asString()];
        
        Json::Value positionO = object["position"];
        vec3 position(positionO[0].asFloat(), positionO[1].asFloat(), positionO[2].asFloat());
        Json::Value rotationO = object["rotation"];
        vec3 rotation(rotationO[0].asFloat(), rotationO[1].asFloat(), rotationO[2].asFloat());
        Json::Value scaleO = object["scale"];
        vec3 scale(scaleO[0].asFloat(), scaleO[1].asFloat(), scaleO[2].asFloat());
        
        Object* obj = new Object(mesh, object.get("name", "Object").asString(), position, rotation, scale, mat);
        
        scene->addChild(obj);
    }
    
    // Create cameras
    for (Json::Value camera : root["cameras"]) {
        Camera* cam;
        string name = camera.get("name", "Camera").asString();
        
        vec3 position(camera["position"][0].asFloat(), camera["position"][1].asFloat(), camera["position"][2].asFloat());
        vec3 rotation(camera["rotation"][0].asFloat(), camera["rotation"][1].asFloat(), camera["rotation"][2].asFloat());
        
        if (camera.get("type", "default").asString() == "free") {
            cam = new FreeCamera(name, position, rotation);
        } else {
            cam = new Camera(name, position, rotation);
        }
        
        scene->addChild(cam);
        
        if (name == attachedCamera) {
            scene->attachCamera(cam);
        }
    }
    
    // Create lights
    for (Json::Value light : root["lights"]) {
        Child* li;
        string name = light.get("name", "Camera").asString();
        string type = light.get("type", "none").asString();
        
        vec3 position(light["position"][0].asFloat(), light["position"][1].asFloat(), light["position"][2].asFloat());
        
        if (type == "point") {
            float constant = light["constant"].asFloat();
            float linear = light["linear"].asFloat();
            float quadratic = light["quadratic"].asFloat();
            
            li = new PointLight(name, position, constant, linear, quadratic);
            
            scene->addPointLight((PointLight *)li);
        } else {
            throw runtime_error("Nonexisting light type specified in scene JSON");
        }
        
        scene->addChild(li);
    }
    
    return scene;
}
