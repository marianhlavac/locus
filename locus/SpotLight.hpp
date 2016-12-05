//
//  SpotLight.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include "Object.hpp"

class SpotLight : public Object {
public:
    SpotLight(string name, vec3 position);
    void updateToUniform();
};

#endif /* SpotLight_hpp */
