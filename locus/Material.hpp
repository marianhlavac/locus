//
//  Material.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <SFML/OpenGL.hpp>
#include <string>

#include "Texture.hpp"

using namespace std;

struct MaterialVertexShader {
    const string src;
    MaterialVertexShader(const string src) : src(src) {}
};

struct MaterialFragmentShader {
    const string src;
    MaterialFragmentShader(const string src) : src(src) {}
};

class Material {
public:
    Material(MaterialVertexShader vertShader, MaterialFragmentShader fragShader, bool link);
    void use();
    static Material* solid();
    GLint getAttribLocation(const char* name);
private:
    Texture* tex;
    const GLuint shaderProgram;
    GLuint compileShader(GLenum type, const string& source);
};

#endif /* Material_hpp */
