//
//  TextRenderer.cpp
//  locus
//
//  Created by Marián Hlaváč on 10/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "TextRenderer.hpp"

TextRenderer::TextRenderer(const string& fontface, int faceSize, Shader* shader) : shader(shader) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw runtime_error("Can't load FreeType library");
    }
    
    FT_Face face;
    if (FT_New_Face(ft, fontface.c_str(), 0, &face)) {
        throw runtime_error("Can't load font face");
    }
    
    FT_Set_Pixel_Sizes(face, 0, faceSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Prepare all characters
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            throw runtime_error("Failed to load glyph from face");
        }
        
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        
        TextRendererChar trc(texture, ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), (GLuint)face->glyph->advance.x);
        
        characters.insert(make_pair(c, trc));
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

TextRendererChar TextRenderer::getCharacter(GLchar character) {
    return characters[character];
}

Shader* TextRenderer::getShader() {
    return shader;
}

void TextRenderer::use() {
    shader->use();
}
