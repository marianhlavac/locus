//
//  Texture.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Texture.hpp"

#include <SOIL/SOIL.h>

Texture::Texture(unsigned char* image, int width, int height) : size(vec2(width, height)) {
    glGenTextures(1, &texture);
    bind();
    generateTexture(image);
    SOIL_free_image_data(image);
    unbind();
}

Texture* Texture::loadFromFile(const string& filename) {
    int width, height;
    
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    return new Texture(image, width, height);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generateTexture(unsigned char* image) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
}
