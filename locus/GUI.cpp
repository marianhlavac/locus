//
//  GUI.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "GUI.hpp"

map<string, vector<string>> configItemLabels = {
    make_pair("render", vector<string> {"wireframe", "solid", "textured"}),
    make_pair("lights", vector<string> {"unlit", "lit", "lit baked"}),
    make_pair("animation", vector<string> {"off", "on"})
};

int menuLeft = 60;
int menuTopInv = 480;

double lastPressElapsed = 0;

GUI::GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial, map<string, int>* configuration) : regularFont(regularFont), boldFont(boldFont), graphic2Dmaterial(graphic2Dmaterial), configuration(configuration) { }

void GUI::init(string navBarTextureFile) {
    // navbar
    navBarTex = Texture::loadFromFile(navBarTextureFile);
    Material* navBarMat = graphic2Dmaterial->clone();
    navBarMat->setTexture(navBarTex);
    navBar = new Graphic2D(navBarMat, vec2(0), vec2(1280, 171));
    
    // config texts
    int y = 0;
    for (auto configItem : *configuration) {
        Text2D* text = new Text2D(configItem.first, boldFont, vec2(menuLeft, menuTopInv - y), vec3(1), 0.4f);
        texts.insert(make_pair(configItem.first + "_label", text));
        y += 24;
        
        int x = 0;
        for (auto configItemLabel : configItemLabels[configItem.first]) {
            Text2D* text = new Text2D(configItemLabel, regularFont, vec2(menuLeft + x, menuTopInv - y), vec3(1), 0.75f);
            texts.insert(make_pair(configItem.first + "_" + configItemLabel, text));
            x += 100;
        }
        y += 48;
    }
    
    selectorIndicator = new Text2D(">", boldFont, vec2(menuLeft - 20, menuTopInv), vec3(1), 0.5f);
    
    configItemsCount = (int)configuration->size();
    configItemSel = 0;
}

void GUI::draw() {
    navBar->draw();
    
    int y = 0;
    for (auto configItem : *configuration) {
        y += 24;
        int x = 0;
        for (auto configItemLabel : configItemLabels[configItem.first]) {
            Text2D* text = texts[configItem.first + "_" + configItemLabel];
            text->setPosition(vec2(menuLeft + x, menuTopInv - y));
            x += text->getSize().x + 50;
        }
        y += 48;
    }
    
    for (auto text : texts) {
        text.second->draw();
    }
    
    selectorIndicator->setPosition(vec2(menuLeft - 20, menuTopInv - 72 * configItemSel));
    selectorIndicator->draw();
}

void GUI::update(Window* window, double elapsed) {
    
    if (elapsed < lastPressElapsed + 0.25f) return;
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
        configItemSel--;
        lastPressElapsed = elapsed;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        configItemSel++;
        lastPressElapsed = elapsed;
    }
}
