//
//  Camera.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Object.hpp"

#include <glm/glm.hpp>

using namespace glm;

class Camera : public Object {
public:
    Camera(string name, vec3 position, vec2 view);
    virtual mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    vec3 getDirection();
    vec2 getView();
    void setView(vec2 view);
protected:
    vec2 view;
    vec3 direction;
};

#endif /* Camera_hpp */
