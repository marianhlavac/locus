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

Camera::Camera(string name, vec3 position, vec2 view) : Object(name, position, vec3(0.0f), vec3(1.0f)), view(view) {
    
}

mat4 Camera::getViewMatrix() {
    direction = vec3(cos(view.y) * sin(view.x), sin(view.y), cos(view.y) * cos(view.x));
    return lookAt(position, position + direction, vec3(0, 1, 0));
}

mat4 Camera::getProjectionMatrix() {
    return perspective( radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
}

vec3 Camera::getDirection() {
    return direction;
}

vec2 Camera::getView() {
    return view;
}

void Camera::setView(vec2 view) {
    this->view = view;
}
