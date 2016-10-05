//
//  Window.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <SFML/OpenGL.hpp>

#include "Window.hpp"

Window::Window(sf::Window& sfWindow, sf::Color& bkgColor) : window(sfWindow), color(bkgColor) {
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    sf::Vector2u windowSize = sfWindow.getSize();
    glViewport(0, 0, windowSize.x, windowSize.y);
}

Window *Window::createWindow(int width, int height) {
    sf::ContextSettings settings(24, 0, 4, 4, 1);
    sf::Color* bkg = new sf::Color();
    sf::Window* win = new sf::Window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, settings);
    win->setVerticalSyncEnabled(true);
    return new Window(*win, *bkg);
}

bool Window::isOpen() {
    return window.isOpen();
}

void Window::close() {
    window.close();
}

bool Window::pollEvent(sf::Event &event) {
    return window.pollEvent(event);
}

void Window::drawScene(Scene scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene.draw();
    window.display();
}
