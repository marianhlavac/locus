//
//  Window.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Window.hpp"

Window::Window(int width, int height) : width(width), height(height) {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    
    glfwSetWindowUserPointer(window, this);
    
    glfwSwapInterval(1);
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::attachScene(Scene *scene) {
    this->scene = scene;
}

Scene* Window::getAttachedScene() {
    return scene;
}

void Window::activate() {
    glfwMakeContextCurrent(window);
    
    
    glClearColor(0.27f, 0.46f, 0.76f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Window::beginDraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endDraw() {
    glfwSwapBuffers(window);
}

bool Window::hasBeenClosed() {
    return glfwWindowShouldClose(window);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}
