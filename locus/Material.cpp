//
//  Material.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

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

Material::Material(MeshShader* vertShader, MeshShader* fragShader, Texture* texture) : tex(texture) {
    program = new MeshShaderProgram(vertShader, fragShader, true);
}

Material::~Material() {
    delete program;
}

Material* Material::solid() {
    MeshShader* vtxShader = new MeshShader(GL_VERTEX_SHADER, defL_solid_mat_vertex_shader1);
    MeshShader* frgShader = new MeshShader(GL_FRAGMENT_SHADER, defL_solid_mat_fragment_shader1);
    
    return new Material(vtxShader, frgShader, nullptr);
}

MeshShaderProgram* Material::getProgram() {
    return program;
}

void Material::use() {
    glUseProgram(program->id);
}
