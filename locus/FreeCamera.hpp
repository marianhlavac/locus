//
//  FreeCamera.hpp
//  locus
//
//  Created by Marián Hlaváč on 31/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef FreeCamera_hpp
#define FreeCamera_hpp


#include "Camera.hpp"
#include "Window.hpp"

#include <glm/glm.hpp>

using namespace glm;

class FreeCamera : public Camera {
public:
    FreeCamera(string name, vec3 position);
    void update(Window* window);
    mat4 getViewMatrix() override;
private:
    float velocity;
};

#endif /* FreeCamera_hpp */
