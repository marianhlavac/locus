//
//  DirectionalLight.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(string name, vec3 position, vec3 color) : Object(name, position), color(color) {
    this->isDrawable = false;
}

void DirectionalLight::setColor(vec3 color) {
    this->color = color;
}

vec3 DirectionalLight::getColor() {
    return color;
}
