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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SOIL_free_image_data(image);
    unbind();
}

Texture::Texture(vector<pair<unsigned char*, vec2>> images) {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    bindCubemap();
    generateCubemap(images);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    unbindCubemap();
}

Texture* Texture::loadFromFile(const string& filename) {
    int width, height;
    
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    return new Texture(image, width, height);
}

Texture* Texture::loadCubemap(vector<string> filenames) {
    vector<pair<unsigned char*, vec2>> images;
    
    for (string filename : filenames) {
        int width, height;
        
        unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        images.push_back(make_pair(image, vec2(width, height)));
    }
    
    return new Texture(images);
}

void Texture::bind(GLenum active) {
    glActiveTexture(active);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::bind() {
    bind(GL_TEXTURE0);
}

void Texture::bindCubemap() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
}

void Texture::unbind(GLenum active) {
    glActiveTexture(active);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::unbind() {
    unbind(GL_TEXTURE0);
}

void Texture::unbindCubemap() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture::generateTexture(unsigned char* image) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::generateCubemap(vector<pair<unsigned char*, vec2>> images) {
    int i = 0;
    for (auto image : images) {
        unsigned char* imgdata = image.first;
        vec2 size = image.second;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
        i++;
    }
}
