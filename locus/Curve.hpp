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

//! Catmull-Rom curve
class Curve {
public:
    Curve();
    Curve(vector<vec3> points);
    vec3 calc(float t);
    vec3 calcD(float t);
    vector<vec3> points;
    void addPoint(vec3 point);
private:
    vector<vec3> getPoints(float t);
};

#endif /* Curve_hpp */
