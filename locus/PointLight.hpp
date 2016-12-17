//
//  PointLight.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp


#include "Object.hpp"

#include <glm/glm.hpp>

using namespace glm;

class PointLight : public Object {
public:
    PointLight(string name, vec3 position, float constant, float linear, float quadratic);
    float getConstant();
    float getLinear();
    float getQuadratic();
private:
    float constant;
    float linear;
    float quadratic;
};

#endif /* PointLight_hpp */
