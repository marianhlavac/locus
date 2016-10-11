//
//  Scene.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(string name) : name(name) {
    
}

string Scene::getName() {
    return name;
}

list<Object> Scene::getChildren() {
    return children;
}

Object Scene::getChildByName(string childName) {
    auto it = find(children.begin(), children.end(), childName);
    
    if (it == children.end()) {
        throw runtime_error("There is no children named '" + childName + "' in scene '" + name + "'.");
    }
    
    return *it;
}

void Scene::addChild(Object child) {
    children.push_back(child);
}
