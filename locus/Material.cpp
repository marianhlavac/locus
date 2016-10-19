//
//  Material.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <vector>

#include "Material.hpp"

using namespace std;

std::string defL_solid_mat_vertex_shader1 =
    "#version 410 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main() {\n"
    "  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\n";

std::string defL_solid_mat_fragment_shader1 =
    "#version 410 core\n"
    "out vec4 color;"
    "void main() {\n"
    "  color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n";

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
    MeshShader* vtxShader = new MeshShader(GL_VERTEX_SHADER, defL_solid_mat_vertex_shader1);
    MeshShader* frgShader = new MeshShader(GL_FRAGMENT_SHADER, defL_solid_mat_fragment_shader1);
    
    vector<std::string> attribs = {
        "position"
    };
    
    vector<std::string> uniforms = { };
    
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
