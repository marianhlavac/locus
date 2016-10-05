//
//  Material.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Material.hpp"

using namespace std;

Material::Material(MaterialVertexShader vertShader, MaterialFragmentShader fragShader, bool link = true) : shaderProgram(glCreateProgram()) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertShader.src);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragShader.src);
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    if (link) {
        glLinkProgram(shaderProgram);
    }
    
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar error[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, error);
        throw runtime_error(error);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); // TODO: are you sure?
}

GLuint Material::compileShader(GLenum type, const string &source) {
    GLuint shader;
    shader = glCreateShader(type);
    const char* sourcec = source.c_str();
    glShaderSource(shader, 1, &sourcec, NULL);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar error[512];
        glGetShaderInfoLog(shader, 512, NULL, error);
        throw runtime_error(error);
    }
    
    return shader;
}

void Material::use() {
    glUseProgram(shaderProgram);
}

Material* Material::solid() {
    MaterialVertexShader mvs("#version 410 core\nlayout (location = 0) in vec3 position; void main() { gl_Position = vec4(position.x, position.y, position.z, 1.0); }\n\0");
    MaterialFragmentShader mfs("#version 410 core\nout vec4 color; void main() { color = vec4(0.8f, 0.8f, 0.8f, 1.0f); }\n\0");
    return new Material(mvs, mfs, true);
}

GLint Material::getAttribLocation(const char* name) {
    return glGetAttribLocation(shaderProgram, name);
}
