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
    
    if (it == children.end()) {
        throw runtime_error("There is no children named '" + childName + "' in scene '" + name + "'.");
    }
    
    return *it;
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
