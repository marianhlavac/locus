//
//  Shader.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(const string vertSrc, const string fragSrc, bool detach) {
    // Compile shader
    vertexShaderId = compileShader(GL_VERTEX_SHADER, vertSrc);
    fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    
    // Create a shader program
    id = glCreateProgram();
    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glLinkProgram(id);
    
    // Get linkage result
    GLint result = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        GLchar* infolog = new GLchar[len + 1];
        glGetShaderInfoLog(id, len, NULL, infolog);
        
        cerr << " -- Shader linking error:" << endl << (char*)infolog << endl;
        
        throw new std::runtime_error("Shader linking error");
    }
    
    // Detach shaders if needed
    if (detach) {
        glDetachShader(id, vertexShaderId);
        glDetachShader(id, fragmentShaderId);
    }
}

Shader::Shader(const string vertSrc, const string fragSrc) : Shader(vertSrc, fragSrc, true) {};

Shader::~Shader() {
    glDeleteShader(id);
}

GLuint Shader::compileShader(GLenum type, const string source) {
    GLuint id = glCreateShader(type);
    
    // Compile the shader code
    const GLchar * srcC = source.c_str();
    glShaderSource(id, 1, &srcC, NULL);
    glCompileShader(id);
    
    // Get compilation result
    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        GLchar* infolog = new GLchar[len + 1];
        glGetShaderInfoLog(id, len, NULL, infolog);
        
        cerr << " -- Shader compilation error:" << endl << (char*)infolog << endl;
        
        glDeleteShader(id);
        throw new std::runtime_error("Shader compilation error");
    }
    
    return id;
}

void Shader::use() {
    glUseProgram(id);
}

Shader* Shader::fromFile(const string vertSrcFilename, const string fragSrcFilename) {
    ifstream vertFile(vertSrcFilename);
    ifstream fragFile(fragSrcFilename);
    
    if (!vertFile.is_open()) throw runtime_error("Vertex shader file not found");
    if (!fragFile.is_open()) throw runtime_error("Fragment shader file not found");
    
    string vertShaderCode((istreambuf_iterator<char>(vertFile)), istreambuf_iterator<char>());
    string fragShaderCode((istreambuf_iterator<char>(fragFile)), istreambuf_iterator<char>());
    
    return new Shader(vertShaderCode, fragShaderCode);
}

GLint Shader::getAttribLocation(const std::string& name) {
    return glGetAttribLocation(id, name.c_str());
}

GLint Shader::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}

void Shader::setUniform(const std::string &name, mat4 value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setUniform(const std::string &name, vec3 value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string &name, GLfloat value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, GLuint value) {
    glUniform1ui(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &target, int id, const std::string &name, vec3 value) {
    glUniform3f(getUniformLocation(target + "[" + to_string(id) + "]." + name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string &target, int id, const std::string &name, GLfloat value) {
    glUniform1f(getUniformLocation(target + "[" + to_string(id) + "]." + name), value);
}

void Shader::setUniform(const std::string &target, int id, const std::string &name, GLuint value) {
    glUniform1ui(getUniformLocation(target + "[" + to_string(id) + "]." + name), value);
}

void Shader::setLightsCount(GLuint directionalLights, GLuint pointLights, GLuint spotLights) {
    setUniform("directionalLightsCount", directionalLights);
    setUniform("pointLightsCount", pointLights);
    setUniform("spotLightsCount", spotLights);
}

void Shader::setADS(string target, int id, vec3 ambient, vec3 diffuse, vec3 specular) {
    setUniform(target, id, "ambient", ambient);
    setUniform(target, id, "diffuse", diffuse);
    setUniform(target, id, "specular", specular);
}
