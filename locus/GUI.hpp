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
#include "Window.hpp"

using namespace std;

class GUI {
public:
    GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial, map<string, int>* configuration);
    void init(string navBarTextureFile);
    void draw();
    void update(Window* window, double elapsed);
private:
    TextRenderer* regularFont;
    TextRenderer* boldFont;
    Material* graphic2Dmaterial;
    Texture* navBarTex;
    Graphic2D* navBar;
    map<string, int>* configuration;
    map<string, Text2D*> texts;
    Text2D* selectorIndicator;
    int configItemSel;
    int configItemsCount;
};

#endif /* GUI_hpp */
