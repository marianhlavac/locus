//
//  FreeCamera.cpp
//  locus
//
//  Created by Marián Hlaváč on 24/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "FreeCamera.hpp"
#include <glm/gtc/quaternion.hpp>

FreeCamera::FreeCamera(string name, vec3 position, vec3 rotation) : Camera(name, position, rotation), velocity(0) {
}

void FreeCamera::update(Window* window, float deltaTime) {
    double xpos, ypos;
    glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
    
    fquat rot;
    
    rot = rotate(rot, (float)xpos / window->getWidth() * MOUSE_SENSITIVITY, vec3(0, 1, 0));
    rot = rotate(rot, (float)ypos / window->getHeight() * MOUSE_SENSITIVITY, vec3(1, 0, 0) * rot);
    
    setRotation(rot);
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        if (velocity.y < MAX_VELOCITY) velocity.y += 2.0f;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        if (velocity.y > -MAX_VELOCITY) velocity.y -= 2.0f;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        if (velocity.x < MAX_VELOCITY) velocity.x += 2.0f;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        if (velocity.x > -MAX_VELOCITY) velocity.x -= 2.0f;
    }
    
    position += vec3(-velocity.x, 0, -velocity.y) * rotation * deltaTime;
    if (length(velocity) < 0 || length(velocity) > 0) velocity = velocity * (1 - FRICTION);
}
