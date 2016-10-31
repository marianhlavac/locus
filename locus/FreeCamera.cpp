//
//  FreeCamera.cpp
//  locus
//
//  Created by Marián Hlaváč on 31/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "FreeCamera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>

#define MOUSE_SENSITIVITY 4.0f
#define MAX_VELOCITY 2.0f

FreeCamera::FreeCamera(string name, vec3 position) : Camera(name, position, vec3(0)) {
    
}

void FreeCamera::update(Window* window) {
    double xpos, ypos;
    glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
    
    view = vec2(-xpos / window->getWidth(), ypos / window->getHeight()) * MOUSE_SENSITIVITY;
    direction = vec3(cos(view.y) * sin(view.x), sin(view.y), cos(view.y) * cos(view.x));
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
        if (velocity < MAX_VELOCITY) velocity += 0.05f;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (velocity > -MAX_VELOCITY) velocity -= 0.05f;
    }
    
    position += velocity * direction;
    if (velocity < 0) velocity -= velocity * 0.10f;
    else if (velocity > 0) velocity -= velocity * 0.10f;
}

mat4 FreeCamera::getViewMatrix() {
    return lookAt(position, position + direction, vec3(0, 1, 0));
}
