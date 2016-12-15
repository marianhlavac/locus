//
//  Child.cpp
//  locus
//
//  Created by Marián Hlaváč on 26/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Child.hpp"

string Child::getName() {
    return name;
}

void Child::setName(string name) {
    this->name = name;
}

list<Child*> Child::getChildren() {
    return children;
}

Child* Child::getChildByName(string childName) {
    auto it = find_if(children.begin(), children.end(), [&] (Child* const &p) { return p->getName() == childName; });
    
    if (it != children.end()) return *it;
    
    for (Child* child : children) {
        auto it = child->getChildByNameRecursive(childName);
        if (it != child->children.end()) return *it;
    }
    
    throw runtime_error("There is no child named " + childName + " in scene.");
}

list<Child*>::iterator Child::getChildByNameRecursive(string childName) {
    auto it = find_if(children.begin(), children.end(), [&] (Child* const &p) { return p->getName() == childName; });
    
    if (it != children.end()) return it;
    
    for (Child* child : children) {
        auto it = child->getChildByNameRecursive(childName);
        if (it != child->children.end()) return it;
    }
}

void Child::addChild(Child* child) {
    children.push_back(child);
}

void Child::removeChild(Child* child) {
    children.remove(child);
}

void Child::removeChildByName(string childName) {
    removeChild(getChildByName(childName));
}
