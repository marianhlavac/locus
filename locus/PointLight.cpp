//
//  PointLight.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "PointLight.hpp"

PointLight::PointLight(string name, vec3 position, vec3 color, float constant, float linear, float quadratic) : Object(name, position), constant(constant), linear(linear), quadratic(quadratic), color(color) {
    this->isDrawable = false;
}

float PointLight::getConstant() {
    return constant;
}

float PointLight::getLinear() {
    return linear;
}

float PointLight::getQuadratic() {
    return quadratic;
}

void PointLight::setColor(vec3 color) {
    this->color = color;
}

vec3 PointLight::getColor() {
    return color;
}
