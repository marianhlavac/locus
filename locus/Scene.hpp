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

using namespace std;

class Scene {
public:
    Scene(string name);
    string getName();
    list<Object> getChildren();
    Object getChildByName(string name);
    void addChild(Object child);
private:
    string name;
    list<Object> children;
};

#endif /* Scene_hpp */
