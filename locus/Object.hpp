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

/// Object class
class Object : public Child {
public:
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, vec3 scale, Material* mat);
    Object(Mesh* mesh, string name, vec3 position, vec3 rotation, Material* mat);
    Object(Mesh* mesh, string name, vec3 position, Material* mat);
    Object(string name, vec3 position, vec3 rotation, vec3 scale);
    Object(string name, vec3 position, vec3 rotation);
    Object(string name, vec3 position);

    /// Draws the object.
    void draw();

    /// Draws the object with specified forced material.
    void draw(Material* forcedMaterial);

    /// Draws the object, keeping some properties from parent object.
    void draw(Object* parent);

    /// Draws the object, keeping props from parent and with specified forced material.
    void draw(Object* parent, Material* forcedMaterial);

    /// Traverse drawing cascade through non-drawable object. Doesn't draw this object,
    /// but draws all children of this object.
    void traverse(Object* parent);

    void traverse(Object* parent, Material* forcedMaterial);

    /// Gets object position.
    vec3 getPosition();

    /// Gets object rotation in euler angles.
    vec3 getRotation(vec3 target);

    /// Gets object rotation as quaternion.
    quat getRotation();

    /// Gets object scale.
    vec3 getScale();

    /// Sets object position.
    void setPosition(vec3 position);

    /// Sets object rotation in quaternion.
    void setRotation(fquat rotation);

    /// Sets object rotation in euler angles.
    void setRotation(vec3 eulerAngles);

    /// Sets object scale.
    void setScale(vec3 scale);

    /// Gets object's transformation matrix (MVP).
    mat4 getTransformationMatrix();

    /// Rotates the object relatively by specified degrees in euler angles.
    void rotateBy(vec3 eulerAngles);

    /// Sets object's selection id. Used for picking objects with mouse.
    void setSelectionId(int selectionId);

    /// Gets object's selection id.
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
