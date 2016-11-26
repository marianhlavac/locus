//
//  Scene.hpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <string>
#include <list>

#include "Object.hpp"
#include "Camera.hpp"

#include "Child.hpp"

using namespace std;

class Scene : public Child {
public:
    Scene(string name);
    void attachCamera(Camera* camera);
    Camera* getAttachedCamera();
    void draw();
private:
    Camera* camera;
};

#endif /* Scene_hpp */
