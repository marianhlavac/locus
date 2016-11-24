//
//  FreeCamera.hpp
//  locus
//
//  Created by Marián Hlaváč on 24/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef FreeCamera_hpp
#define FreeCamera_hpp

#define MOUSE_SENSITIVITY 0.005f
#define MAX_VELOCITY 2.0f

#include "Camera.hpp"
#include "Window.hpp"

class FreeCamera : public Camera {
public:
    FreeCamera(string name, vec3 position, vec3 rotation);
    void update(Window* window);
private:
    float velocity;
};

#endif /* FreeCamera_hpp */
