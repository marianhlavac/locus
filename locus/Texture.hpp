//
//  Texture.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>

using namespace std;
using namespace glm;

class Texture {
public:
    Texture(unsigned char* image, int width, int height);
    static Texture* loadFromFile(const string& filename);
    void bind();
    static void unbind();
private:
    vec2 size;
    GLuint texture;
    void generateTexture(unsigned char* image);
};

#endif /* Texture_hpp */
