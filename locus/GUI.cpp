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
    make_pair("animations", vector<string> {"off", "on"}),
    make_pair("collisions", vector<string> {"off", "on"}),
    make_pair("scene", vector<string> {"stop", "play"}),
    make_pair("camera", vector<string> {"primary", "free camera", "secondary"})
};

int menuLeft = 60;
int menuTopInv = 560;

double lastPressElapsed = 0;

GUI::GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial, map<string, int>* configuration) : regularFont(regularFont), boldFont(boldFont), graphic2Dmaterial(graphic2Dmaterial), configuration(configuration) {
    navbarProjection = vec4(0, 1280, 200, 720);
    menuProjection = vec4(640, 1280, 0, 720);
    displayed = true;
}

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
        configIds.push_back(configItem.first);
    }
    
    selectorIndicator = new Text2D(">", boldFont, vec2(menuLeft - 20, menuTopInv), vec3(1), 0.5f);
    
    configItemsCount = (int)configuration->size();
    configItemSel = 0;
}

void GUI::draw() {
    int leftXProjTarget = displayed ? 0 : 640;
    int topYProjTarget = displayed ? 0 : 200;
    navbarProjection.z += (topYProjTarget - navbarProjection.z) / 8.0f;
    menuProjection.x += (leftXProjTarget - menuProjection.x) / 8.0f;
    navBar->draw(navbarProjection);
    
    int y = 0;
    for (auto configItem : *configuration) {
        y += 24;
        int x = 0;
        int i = 0;
        for (auto configItemLabel : configItemLabels[configItem.first]) {
            Text2D* text = texts[configItem.first + "_" + configItemLabel];
            text->setPosition(vec2(menuLeft + x, menuTopInv - y));
            text->setRenderer((*configuration)[configItem.first] == i ? boldFont : regularFont);
            text->setColor((*configuration)[configItem.first] == i ? vec3(1) : vec3(0.5f));
            x += text->getSize().x + 50;
            i++;
        }
        y += 48;
    }
    
    for (auto text : texts) {
        text.second->draw(menuProjection);
    }
    
    selectorIndicator->setPosition(vec2(menuLeft - 20, menuTopInv - 72 * configItemSel));
    selectorIndicator->draw(menuProjection);
}

void GUI::update(Window* window, double elapsed) {
    if (elapsed < lastPressElapsed + 0.25f) return;
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) {
        (*configuration)["scene"] = (*configuration)["scene"] == 1 ? 0 : 1;
        lastPressElapsed = elapsed;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        displayed = !displayed;
        lastPressElapsed = elapsed;
    }
    
    if (!displayed) return;
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
        if (configItemSel > 0) configItemSel--;
        lastPressElapsed = elapsed;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (configItemSel < configuration->size() - 1) configItemSel++;
        lastPressElapsed = elapsed;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
        string tid = configIds[configItemSel];
        if ((*configuration)[tid] > 0) {
            (*configuration)[tid]--;
        }
        lastPressElapsed = elapsed;
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
        string tid = configIds[configItemSel];
        if ((*configuration)[tid] < configItemLabels[tid].size() - 1) {
            (*configuration)[tid]++;
        }
        lastPressElapsed = elapsed;
    }
}
