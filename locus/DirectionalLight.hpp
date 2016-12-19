//
//  DirectionalLight.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp


#include "Object.hpp"

//! Directional light object
class DirectionalLight : public Object {
public:
    DirectionalLight(string name, vec3 rotation, vec3 color);
    void updateToUniform();
    void setColor(vec3 color);
    vec3 getColor();
private:
    vec3 color;
};

#endif /* DirectionalLight_hpp */
