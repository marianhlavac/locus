//
//  Camera.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Camera.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(string name, vec3 position, vec3 center) : Object(name, position, vec3(0.0f), vec3(1.0f)), center(center) {
    
}

mat4 Camera::getViewMatrix() {
    return lookAt(position, center, vec3(0, 1, 0));
}

mat4 Camera::getProjectionMatrix() {
    return perspective( radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
}
