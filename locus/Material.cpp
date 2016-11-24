//
//  Material.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <vector>
#include <fstream>
#include <string>
#include <streambuf>

#include "Material.hpp"
#include "ResourcePath.hpp"

using namespace std;

Material::Material(MeshShader* vertShader, MeshShader* fragShader, vector<string> & attributes, vector<string> & uniforms){
    program = new MeshShaderProgram(vertShader, fragShader, true);
    
    for (string name : attributes) {
        saveAttribLocation(name);
    }
    
    for (string name : uniforms) {
        saveUniformLocation(name);
    }
}

Material::~Material() {
    delete program;
}

Material* Material::solid() {
    
    vector<std::string> attribs = {
        "position",
        "normal"
    };
    
    vector<std::string> uniforms = {
        "mvp"
    };
    
    return fromFile(resourcePath() + "Shaders/Solid.vert", resourcePath() + "Shaders/Solid.frag", attribs, uniforms);
}

Material* Material::fromFile(const std::string& vertShaderFilename, const std::string& fragShaderFilename, vector<string> attribs, vector<string> uniforms) {
    ifstream vertFile(vertShaderFilename);
    ifstream fragFile(fragShaderFilename);
    
    string vertShaderCode((istreambuf_iterator<char>(vertFile)), istreambuf_iterator<char>());
    string fragShaderCode((istreambuf_iterator<char>(fragFile)), istreambuf_iterator<char>());
    
    MeshShader* vtxShader = new MeshShader(GL_VERTEX_SHADER, vertShaderCode);
    MeshShader* frgShader = new MeshShader(GL_FRAGMENT_SHADER, fragShaderCode);
    
    return new Material(vtxShader, frgShader, attribs, uniforms);
}

GLint Material::getAttribLocation(const std::string& name) {
    return attribLocations.at(name);
}

GLint Material::getUniformLocation(const std::string& name) {
    return uniformLocations.at(name);
}

vector<string> Material::getAllAttribs() {
    vector<string> v;
    
    for (pair<string, GLuint> i : attribLocations) {
        v.push_back(i.first);
    }
    
    return v;
}

vector<string> Material::getAllUniforms() {
    vector<string> v;
    
    for (pair<string, GLuint> i : uniformLocations) {
        v.push_back(i.first);
    }
    
    return v;
}

void Material::saveAttribLocation(const std::string& name) {
    attribLocations[name] = glGetAttribLocation(program->id, name.c_str());
}

void Material::saveUniformLocation(const std::string& name) {
    uniformLocations[name] = glGetUniformLocation(program->id, name.c_str());
}

MeshShaderProgram* Material::getProgram() {
    return program;
}

void Material::use() {
    glUseProgram(program->id);
}

void Material::setUniformMf4(const std::string &name, mat4 value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
