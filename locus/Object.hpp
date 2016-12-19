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

//! Object class
class Object : public Child {
public:
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale, Material* mat);
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, Material* mat);
    Object(Mesh* mesh, string name, vec3 position, Material* mat);
    Object(string name, vec3 position, vec3 rotation, vec3 scale);
    Object(string name, vec3 position, vec3 rotation);
    Object(string name, vec3 position);
    void draw();
    void draw(Material* forcedMaterial);
    void draw(Object* parent);
    void draw(Object* parent, Material* forcedMaterial);
    void traverse(Object* parent);
    void traverse(Object* parent, Material* forcedMaterial);
    vec3 getPosition();
    vec3 getRotation(vec3 target);
    quat getRotation();
    vec3 getScale();
    void setPosition(vec3 position);
    void setRotation(fquat rotation);
    void setRotation(vec3 eulerAngles);
    void setScale(vec3 scale);
    mat4 getTransformationMatrix();
    void rotateBy(vec3 eulerAngles);
    void setSelectionId(int selectionId);
    int getSelectionId();
protected:
    Mesh* mesh;
    Material* material;
    vec3 position;
    fquat rotation;
    vec3 scale;
    int selectionId;
};

#endif /* Object_hpp */
