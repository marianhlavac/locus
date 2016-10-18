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
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "Texture.hpp"

using namespace std;

struct MeshShader {
    MeshShader(GLenum type, const std::string src) {
        id = glCreateShader(type);
        
        const GLchar * srcC = src.c_str();
        glShaderSource(id, 1, &srcC, NULL);
        glCompileShader(id);
        
        GLint result = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            throw new std::runtime_error("Shader compilation error");
        }
    }
    ~MeshShader() {
        glDeleteShader(id);
    }
    GLuint id;
};

struct MeshShaderProgram {
    MeshShaderProgram(MeshShader* vertexShader, MeshShader* fragmentShader, bool detach) {
        id = glCreateProgram();
        glAttachShader(id, vertexShader->id);
        glAttachShader(id, fragmentShader->id);
        glLinkProgram(id);
        
        GLint result = GL_FALSE;
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            throw new std::runtime_error("Shader linking error");
        }
        
        if (detach) {
            glDetachShader(id, vertexShader->id);
            glDetachShader(id, fragmentShader->id);
        }
    }
    GLuint id;
};

class Material {
public:
    Material(MeshShader* vertexShader, MeshShader* fragmentShader, vector<string> & attributes, vector<string> & uniforms);
    ~Material();
    static Material* solid();
    MeshShaderProgram* getProgram();
    GLint getAttribLocation(const std::string& name);
    GLint getUniformLocation(const std::string& name);
    vector<string> getAllAttribs();
    vector<string> getAllUniforms();
    void use();
private:
    MeshShaderProgram* program;
    map<std::string, GLuint> attribLocations;
    map<std::string, GLuint> uniformLocations;
    void saveAttribLocation(const std::string& name);
    void saveUniformLocation(const std::string& name);
};

#endif /* Material_hpp */
