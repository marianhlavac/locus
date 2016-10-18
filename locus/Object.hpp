//
//  Object.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"
#include "Material.hpp"

class Object {
public:
    Object(Mesh* mesh, Material* material, sf::Vector3f position, string name);
    Material* getMaterial();
    void draw();
    string getName() const;
    void setName(string name);
private:
    string name;
    Mesh* mesh;
    Material* material;
    sf::Vector3f position;
    sf::Vector3f rotation; // TODO: eeuuuggh, quaternion needed?
};

#endif /* Object_hpp */
