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

/// Texture class
class Texture {
public:
    Texture(unsigned char* image, int width, int height);
    Texture(vector<pair<unsigned char*, vec2>> images);

    /// Loads texture from file using SOIL.
    static Texture* loadFromFile(const string& filename);

    /// Loads cubemap texture set from files using SOIL.
    static Texture* loadCubemap(vector<string> filenames);

    /// Binds texture to specified texture unit.
    /// \param active Active texture from GL_TEXTURE0 to GL_TEXTURE16.
    void bind(GLenum active);

    /// Binds texture to first texture unit.
    void bind();

    /// Binds texture as cubemap to first texture unit.
    void bindCubemap();

    /// Unbinds texture at specified texture unit position.
    /// \param active Active texture from GL_TEXTURE0 to GL_TEXTURE16.
    static void unbind(GLenum active);

    /// Unbinds texture from first texture unit position.
    static void unbind();

    /// Unbinds cubemap texture from first texture unit position.
    static void unbindCubemap();
private:
    vec2 size;
    GLuint texture;
    void generateTexture(unsigned char* image);
    void generateCubemap(vector<pair<unsigned char*, vec2>> images);
};

#endif /* Texture_hpp */
