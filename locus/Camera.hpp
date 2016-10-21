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
    Camera(string name, vec3 position, vec3 rotation);
    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
};

#endif /* Camera_hpp */
