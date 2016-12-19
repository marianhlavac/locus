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

/// Material class
class Material {
public:
    /// Base type of texture.
    static const int TEXTURE_BASE = 0;

    /// Cubemap type of texture.
    static const int TEXTURE_CUBEMAP = 1;

    Material(Shader* shader, Texture* texture, vec3 ambient, vec3 diffuse, vec3 specular);
    Material(Shader* shader, vec3 ambient, vec3 diffuse, vec3 specular);
    Material(Shader* shader);
    Material(Shader* shader, Texture* texture);
    ~Material();

    /// Loads material from .mat file.
    static Material* fromFile(const string& filename);

    /// Clones the material.
    Material* clone();

    /// Use the material.
    void use();

    /// Gets material's assigned shader.
    Shader* getShader();

    /// Gets material's texture. Can be empty or nonexistent.
    Texture* getTexture();

    /// Gets materials' specular map (texture). Can be empty or nonexistent.
    Texture* getSpecularMap();

    void setSpecularMap(Texture* texture);
    void setTexture(Texture* texture);
    void unsetTexture();

    /// Updates the MVP transformation matrix.
    void updateMVP(mat4 modelTransform, mat4 viewTransform, mat4 projectionTransform);

    /// Updates the VP parts of MVP transformation matrix.
    void updateVP(mat4 viewTransform, mat4 projectionTransform);

    /// Updates the M part of MVP transformation matrix.
    void updateM(mat4 modelTransform);

    /// Specifies texture type. Can be TEXTURE_BASE or TEXTURE_CUBEMAP.
    void setTextureType(int textureType);

    /// Sets special animated unlit shader properties.
    void setAnimatedUnlitProps(int tileDiv, float speed);

    /// Ambient component of material.
    vec3 ambient;

    /// Diffuse component of material.
    vec3 diffuse;

    /// Specular component of material.
    vec3 specular;
private:
    Shader* shader;
    bool hasTexture;
    Texture* texture;
    Texture* specularMap;
    bool hasSpecularMap;
    int textureType;
};

#endif /* Material_hpp */
