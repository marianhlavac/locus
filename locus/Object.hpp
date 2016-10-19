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
    Object(Mesh* mesh, vec3 position, string name);
    void draw();
    string getName() const;
    void setName(string name);
private:
    string name;
    Mesh* mesh;
    vec3 position;
    vec3 rotation; // TODO: eeuuuggh, quaternion needed?
};

#endif /* Object_hpp */
