//
//  Curve.hpp
//  locus
//
//  Created by Marián Hlaváč on 14/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Curve_hpp
#define Curve_hpp

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Curve {
public:
    Curve();
    vec3 calc(float t);
    vector<vec3> points;
    void addPoint(vec3 point);
private:
    float poly(float var, float cubic, float square, float linear, float constant);
    int getSegment(float t);
};

#endif /* Curve_hpp */
