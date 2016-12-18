//
//  Text2D.hpp
//  locus
//
//  Created by Marián Hlaváč on 10/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Text2D_hpp
#define Text2D_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "TextRenderer.hpp"

using namespace glm;

class Text2D {
public:
    Text2D(string text, TextRenderer* renderer, vec2 position, vec3 color, float scale);
    void draw(vec4 proj);
    void draw();
    vec3 getColor();
    void setColor(vec3 color);
    void setText(string text);
    vec2 getSize();
    void setPosition(vec2 position);
    void setAlign(int align);
    void setRenderer(TextRenderer* renderer);
    static const int ALIGN_LEFT = 0;
    static const int ALIGN_CENTER = 1;
private:
    string text;
    vec2 position;
    vec2 size;
    MeshVAO vao;
    MeshVBO vbo;
    TextRenderer* renderer;
    vec3 color;
    float scale;
    int align;
};

#endif /* Text2D_hpp */
