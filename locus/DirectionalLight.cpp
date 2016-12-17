//
//  DirectionalLight.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(string name, vec3 position) : Object(name, position) {
    this->isDrawable = false;
}
