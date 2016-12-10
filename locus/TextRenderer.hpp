//
//  TextRenderer.hpp
//  locus
//
//  Created by Marián Hlaváč on 10/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef TextRenderer_hpp
#define TextRenderer_hpp

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "Shader.hpp"

using namespace glm;
using namespace std;

struct TextRendererChar {
    TextRendererChar(GLuint texId, ivec2 size, ivec2 bearing, GLuint advance) : textureId(texId), size(size), bearing(bearing), advance(advance) { };
    TextRendererChar() { };
    GLuint textureId;
    ivec2 size;
    ivec2 bearing;
    GLuint advance;
};

class TextRenderer {
public:
    TextRenderer(const string& fontface, int faceSize, Shader* shader);
    TextRendererChar getCharacter(GLchar character);
    Shader* getShader();
    void use();
private:
    map<GLchar, TextRendererChar> characters;
    Shader* shader;
};

#endif /* TextRenderer_hpp */
