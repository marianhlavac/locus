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
    Material(MeshShader* vertexShader, MeshShader* fragmentShader, Texture* texture);
    ~Material();
    static Material* solid();
    GLint getAttribLocation(const char* name);
    MeshShaderProgram* getProgram();
    void use();
private:
    Texture* tex;
    MeshShaderProgram* program;
    sf::Shader* shader;
};

#endif /* Material_hpp */
