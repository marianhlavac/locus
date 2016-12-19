//
//  Shader.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;

//! Shader class
class Shader {
public:
    Shader(const string vertSrc, const string fragSrc, bool detach);
    Shader(const string vertSrc, const string fragSrc);
    static Shader* fromFile(const string vertSrcFilename, const string fragSrcFilename);
    ~Shader();
    void use();
    GLint getAttribLocation(const std::string& name);
    GLint getUniformLocation(const std::string& name);
    void setUniform(const std::string& name, mat4 value);
    void setUniform(const std::string& name, vec3 value);
    void setUniform(const std::string& name, GLfloat value);
    void setUniform(const std::string& name, GLuint value);
    void setUniform(const std::string& target, int id, const std::string& name, vec3 value);
    void setUniform(const std::string& target, int id, const std::string& name, GLfloat value);
    void setUniform(const std::string& target, int id, const std::string& name, GLuint value);
    void setLightsCount(GLuint directionalLights, GLuint pointLights, GLuint spotLights);
    void setADS(string target, int id, vec3 ambient, vec3 diffuse, vec3 specular);
private:
    GLuint compileShader(GLenum type, const string source);
    GLuint id;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
};

struct ShaderProgram {
    ShaderProgram(Shader* vertexShader, Shader* fragmentShader, bool detach) {

    }
    GLuint id;
};

#endif /* Shader_hpp */
