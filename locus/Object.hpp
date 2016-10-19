//
//  Object.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Material.hpp"
using namespace glm;

class Object {
public:
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale);
    Object(string name, vec3 position, vec3 rotation, vec3 scale);
    void draw(mat4 viewTransformationMatrix);
    string getName() const;
    void setName(string name);
    vec3 getPosition();
    vec3 getRotation();
    vec3 getScale();
    void setPosition(vec3 position);
    void setRotation(vec3 rotation);
    void setScale(vec3 scale);
    mat4 getTransformationMatrix();
private:
    string name;
    Mesh* mesh;
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

#endif /* Object_hpp */
