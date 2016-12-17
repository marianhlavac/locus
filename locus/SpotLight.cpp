//
//  SpotLight.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "SpotLight.hpp"

SpotLight::SpotLight(string name, vec3 position, vec3 rotation, float constant, float linear, float quadratic, float cutOff, float outerCutOff) : Object(name, position, rotation), linear(linear), constant(constant), quadratic(quadratic), cutOff(cutOff), outerCutOff(outerCutOff) {
    this->isDrawable = false;
}

float SpotLight::getConstant() {
    return constant;
}

float SpotLight::getLinear() {
    return linear;
}

float SpotLight::getQuadratic() {
    return quadratic;
}

float SpotLight::getCutOff() {
    return cutOff;
}

float SpotLight::getOuterCutOff() {
    return outerCutOff;
}
