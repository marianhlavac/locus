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
#include <vector>

using namespace std;
using namespace glm;

class Texture {
public:
    Texture(unsigned char* image, int width, int height);
    Texture(vector<pair<unsigned char*, vec2>> images);
    static Texture* loadFromFile(const string& filename);
    static Texture* loadCubemap(vector<string> filenames);
    void bind();
    void bindCubemap();
    static void unbind();
    static void unbindCubemap();
private:
    vec2 size;
    GLuint texture;
    void generateTexture(unsigned char* image);
    void generateCubemap(vector<pair<unsigned char*, vec2>> images);
};

#endif /* Texture_hpp */
