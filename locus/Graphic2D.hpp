//
//  Graphic2D.hpp
//  locus
//
//  Created by Marián Hlaváč on 11/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Graphic2D_hpp
#define Graphic2D_hpp

#include "Texture.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Graphic2D {
public:
    Graphic2D(Material* material, vec2 position, vec2 scale);
    void draw();
    void draw(vec4 proj);
    void setSize(vec2 size);
private:
    Material* material;
    Texture* texture;
    Mesh* mesh;
    vec2 position;
    vec2 size;
};

#endif /* Graphic2D_hpp */
