//
//  Curve.cpp
//  locus
//
//  Created by Marián Hlaváč on 14/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Curve.hpp"

#include <iostream>
#include <fstream>

Curve::Curve() { }

Curve::Curve(vector<vec3> points) : points(points) { }

int mod_p(int i, int n) {
    return (i % n + n) % n;
}

vec3 Curve::calc(float t) {
    vector<vec3> p = getPoints(t);
    t = fmod(t, 1.0f);
    
    return 0.5f * ((p[1]*2.0f) + (-p[0]+p[2])*t + ((p[0]*2.0f)-(p[1]*5.0f)+(p[2]*4.0f)-p[3]) * (float)pow(t,2) + (-p[0]+(p[1]*3.0f)-(p[2]*3.0f)+p[3]) * (float)pow(t,3.0f));
}

vec3 Curve::calcD(float t) {
    vector<vec3> p = getPoints(t);
    t = fmod(t, 1.0f);
    
    return 0.5f * (3.0f*(float)pow(t,2) * (-p[0]+3.0f*p[1]-3.0f*p[2]+p[3]) + 2*t * (2.0f*p[0]-5.0f*p[1]+4.0f*p[2]-p[3]) - p[0] + p[2]);
}

vector<vec3> Curve::getPoints(float t) {
    if (points.size() < 4) {
        throw runtime_error("There must be at least 4 points in curve");
    }
    
    int maxseg = (int)points.size();
    int segment = (int)floor(t);
    t = fmod(t, 1.0f);
    
    return vector<vec3> {
        points[mod_p((segment-1), maxseg)], points[mod_p((segment), maxseg)], points[mod_p((segment+1), maxseg)], points[mod_p((segment+2), maxseg)]
    };
}

void Curve::addPoint(vec3 point) {
    points.push_back(point);
}

Curve* Curve::loadFromFile(string filename) {
    vector<vec3> points;
    ifstream file(filename);
    float x, y, z;
    while (file >> x >> y >> z) {
        points.push_back(vec3(x, y, z));
    }
    
    return new Curve(points);
}
