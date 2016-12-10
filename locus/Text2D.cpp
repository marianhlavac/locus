//
//  Text2D.cpp
//  locus
//
//  Created by Marián Hlaváč on 10/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Text2D.hpp"

Text2D::Text2D(string text, TextRenderer* renderer, vec2 position, vec3 color, float scale) : vao(MeshVAO()), vbo(MeshVBO(GL_ARRAY_BUFFER, NULL, sizeof(GLfloat) * 6 * 4, GL_DYNAMIC_DRAW)), renderer(renderer), color(color), text(text), scale(scale), position(position) {
    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.addAttrib(0, 4, GL_FLOAT, 4, 0);
}

void Text2D::draw() {
    renderer->use();
    renderer->getShader()->setUniform("textColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    vao.bind();
    
    mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    renderer->getShader()->setUniform("mvp", projection);
    
    
    float xadvanced = position.x;
    
    string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        TextRendererChar trc = renderer->getCharacter(*c);
        
        // Quad generation
        GLfloat xpos = xadvanced + trc.bearing.x * scale;
        GLfloat ypos = position.y - (trc.size.y - trc.bearing.y) * scale;
        GLfloat width = trc.size.x * scale;
        GLfloat height = trc.size.y * scale;
        
        GLfloat vertices[6][4] = {
            {xpos, ypos + height, 0, 0},
            {xpos, ypos, 0, 1},
            {xpos + width, ypos, 1, 1},
            {xpos, ypos + height, 0, 0},
            {xpos + width, ypos, 1, 1},
            {xpos + width, ypos + height, 1, 0},
        };
        
        // Bind texture and sub vertices
        glBindTexture(GL_TEXTURE_2D, trc.textureId);
        vbo.subData(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
        
        // Draw quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Advance next glyph
        xadvanced += (trc.advance >> 6) * scale;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    vao.unbind();
}

vec3 Text2D::getColor() {
    return color;
}

void Text2D::setColor(vec3 color) {
    this->color = color;
}

void Text2D::setText(string text) {
    this->text = text;
}
