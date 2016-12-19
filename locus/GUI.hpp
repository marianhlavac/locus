//
//  GUI.hpp
//  locus
//
//  Created by Marián Hlaváč on 11/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef GUI_hpp
#define GUI_hpp

#include "TextRenderer.hpp"
#include "Graphic2D.hpp"
#include "Text2D.hpp"
#include <map>
#include <string>
#include "Window.hpp"

using namespace std;

/// Graphic User Interface
class GUI {
public:
    GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial, map<string, int>* configuration);

    /// Initializes the GUI.
    void init(string navBarTextureFile);

    /// Draws the GUI.
    void draw();

    /// Updates the GUI.
    void update(Window* window, double elapsed);

    /// Is GUI meant to be displayed?
    bool displayed;
private:
    TextRenderer* regularFont;
    TextRenderer* boldFont;
    Material* graphic2Dmaterial;
    Texture* navBarTex;
    Graphic2D* navBar;
    map<string, int>* configuration;
    map<string, Text2D*> texts;
    vector<string> configIds;
    Text2D* selectorIndicator;
    int configItemSel;
    int configItemsCount;
    vec4 navbarProjection;
    vec4 menuProjection;
};

#endif /* GUI_hpp */
