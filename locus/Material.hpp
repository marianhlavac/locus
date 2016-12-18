//
//  Material.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <map>
#include <list>

#include <iostream>

#include "Texture.hpp"
#include "Shader.hpp"

using namespace std;
using namespace glm;

class Material {
public:
    static const int TEXTURE_BASE = 0;
    static const int TEXTURE_CUBEMAP = 1;
    Material(Shader* shader, Texture* texture, vec3 ambient, vec3 diffuse, vec3 specular);
    Material(Shader* shader, vec3 ambient, vec3 diffuse, vec3 specular);
    Material(Shader* shader);
    Material(Shader* shader, Texture* texture);
    ~Material();
    static Material* fromFile(const string& filename);
    Material* clone();
    void use();
    Shader* getShader();
    Texture* getTexture();
    void setTexture(Texture* texture);
    void unsetTexture();
    void updateMVP(mat4 modelTransform, mat4 viewTransform, mat4 projectionTransform);
    void updateVP(mat4 viewTransform, mat4 projectionTransform);
    void updateM(mat4 modelTransform);
    void setTextureType(int textureType);
    void setAnimatedUnlitProps(int tileDiv, float speed);
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
private:
    Shader* shader;
    bool hasTexture;
    Texture* texture;
    int textureType;
};

#endif /* Material_hpp */
