//
//  GUI.cpp
//  locus
//
//  Created by Marián Hlaváč on 11/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "GUI.hpp"

GUI::GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial) : regularFont(regularFont), boldFont(boldFont), graphic2Dmaterial(graphic2Dmaterial) { }

void GUI::init(string navBarTextureFile) {
    navBarTex = Texture::loadFromFile(navBarTextureFile);
    Material* navBarMat = graphic2Dmaterial->clone();
    navBarMat->setTexture(navBarTex);
    navBar = new Graphic2D(navBarMat, vec2(0), vec2(1280, 171));
}

void GUI::draw() {
    navBar->draw();
}
