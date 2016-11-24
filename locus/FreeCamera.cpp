//
//  FreeCamera.cpp
//  locus
//
//  Created by Marián Hlaváč on 24/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "FreeCamera.hpp"

FreeCamera::FreeCamera(string name, vec3 position, vec3 rotation) : Camera(name, position, rotation), velocity(0) {
}

void FreeCamera::update(Window* window) {
    double xpos, ypos;
    glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
    
    setRotation(vec3(ypos / 100.0f, xpos / 100.0f, 0));
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        if (velocity < MAX_VELOCITY) velocity += 0.05f;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        if (velocity > -MAX_VELOCITY) velocity -= 0.05f;
    }
    
    vec3 direction = rotation * vec3(0, 1, 0);
    position += velocity * direction;
    if (velocity < 0) velocity -= velocity * 0.10f;
    else if (velocity > 0) velocity -= velocity * 0.10f;
    
    glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
}
