//
//  Curve.cpp
//  locus
//
//  Created by Marián Hlaváč on 14/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Curve.hpp"

#include <iostream>

Curve::Curve() {
    
}

vec3 Curve::calc(float t) {
    if (points.size() < 4) {
        throw runtime_error("There must be at least 4 points in curve");
    }
    
    int segment = getSegment(t);
    t = fmod(t / 4.0f, 1);
    int maxseg = (int)points.size() - 1;
    
    cout << "pts " << segment << "-" << (segment + 4) % maxseg << " / " << points.size() << endl;
    
    vec3 p0 = points[segment % maxseg];
    vec3 p1 = points[++segment % maxseg];
    vec3 p2 = points[++segment % maxseg];
    vec3 p3 = points[++segment % maxseg];
    
    return 0.5f * (p0 * poly(t, -3, 2, -1, 0) + p1 * poly(t, 3, -5, 0, 2) + p2 * poly(t, -3, 4, 1, 0) + p3 * poly(t, 1, 1, 0, 0));
}

float Curve::poly(float var, float cubic, float square, float linear, float constant) {
    return pow(var, 3) * cubic + pow(var, 2) * square + var * linear + constant;
}

int Curve::getSegment(float t) {
    return fmod(floor(t / 4.0f) * 4.0f, points.size());
}

void Curve::addPoint(vec3 point) {
    points.push_back(point);
}
