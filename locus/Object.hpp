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
#include <glm/gtx/quaternion.hpp>

#include "Mesh.hpp"
#include "Material.hpp"

#include "Child.hpp"

using namespace glm;

class Object : public Child {
public:
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale);
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation);
    Object(Mesh* mesh, string name, vec3 position);
    Object(string name, vec3 position, vec3 rotation, vec3 scale);
    Object(string name, vec3 position, vec3 rotation);
    Object(string name, vec3 position);
    void draw(mat4 viewTransform, mat4 projectionTransform);
    void draw(mat4 modelTransform, mat4 viewTransform, mat4 projectionTransform);
    vec3 getPosition();
    quat getRotation();
    vec3 getScale();
    void setPosition(vec3 position);
    void setRotation(fquat rotation);
    void setRotation(vec3 eulerAngles);
    void setScale(vec3 scale);
    mat4 getTransformationMatrix();
    void rotateBy(vec3 eulerAngles);
protected:
    Mesh* mesh;
    vec3 position;
    fquat rotation;
    vec3 scale;
};

#endif /* Object_hpp */
