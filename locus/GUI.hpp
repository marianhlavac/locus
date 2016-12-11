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

class GUI {
public:
    GUI(TextRenderer* regularFont, TextRenderer* boldFont, Material* graphic2Dmaterial);
    void init(string navBarTextureFile);
    void draw();
private:
    TextRenderer* regularFont;
    TextRenderer* boldFont;
    Material* graphic2Dmaterial;
    Texture* navBarTex;
    Graphic2D* navBar;
};

#endif /* GUI_hpp */
