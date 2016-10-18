//
//  Window.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>

#include "Scene.hpp"

class Window {
public:
    Window(sf::Window* sfWindow, sf::Color* bkgColor);
    static Window* createWindow(int width, int height);
    sf::Window* getWindow();
    bool isOpen();
    void close();
    bool pollEvent(sf::Event& event);
    void attachScene(Scene* scene);
    void draw();
private:
    sf::Window* window;
    sf::Color* color;
    Scene* scene;
};

#endif /* Window_hpp */
