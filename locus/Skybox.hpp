//
//  Skybox.hpp
//  locus
//
//  Created by Marián Hlaváč on 17/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.hpp"

/// Skybox object
class Skybox {
public:
    Skybox(float size, Material* material);
    void draw();
private:
    Mesh* mesh;
    Texture* texture;
    Material* material;
};

#endif /* Skybox_hpp */
