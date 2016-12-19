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

/// Catmull-Rom curve
class Curve {
public:
    Curve();
    Curve(vector<vec3> points);

    /// Calculates the result of curve function in time parameter t.
    /// \param t Time parameter t.
    /// \throws runtime_error When there are less than 4 points in curve specified.
    vec3 calc(float t);

    /// Calculates the derivative of curve function (returns direction).
    /// \param t Time parameter t.
    vec3 calcD(float t);

    /// All points of the curve. At least 4 points are needed.
    vector<vec3> points;

    /// Adds single point to the curve.
    void addPoint(vec3 point);
private:
    vector<vec3> getPoints(float t);
};

#endif /* Curve_hpp */
