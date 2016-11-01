//
//  WavefrontParser.cpp
//  locus
//
//  Created by Marián Hlaváč on 28/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "WavefrontParser.hpp"

#include <iostream>

#define INDICES_OFFSET  1

using namespace std;

WavefrontParserResult* WavefrontParser::parse(const string& filename) {
    WavefrontParserResult* result = new WavefrontParserResult;
    
    ifstream file(filename);
    string line;
    
    GLuint i = 0;
    
    while (getline(file, line)) {
        stringstream ss(line);
        
        string type;
        ss >> type;
        
        if (type == "v") parseVertex(ss, result);
        if (type == "vt") parseUV(ss, result);
        if (type == "vn") parseNormal(ss, result);
        if (type == "f") {
            parseFace(ss, result);
            result->indices.push_back(i++);
            result->indices.push_back(i++);
            result->indices.push_back(i++);
        }
    }

    return result;
}

void WavefrontParser::parseVertex(stringstream& ss, WavefrontParserResult* resultOut) {
    float x, y, z;
    ss >> x >> y >> z;
    resultOut->vertices.push_back(vec3(x, y, z));
}

void WavefrontParser::parseNormal(stringstream& ss, WavefrontParserResult* resultOut) {
    float x, y, z;
    ss >> x >> y >> z;
    resultOut->normals.push_back(vec3(x, y, z));
}

void WavefrontParser::parseUV(stringstream& ss, WavefrontParserResult* resultOut) {
    float x, y;
    ss >> x >> y;
    resultOut->uvs.push_back(vec2(x, y));
}

void WavefrontParser::parseFace(stringstream& ss, WavefrontParserResult* resultOut) {
    string s1, s2, s3;
    ss >> s1 >> s2 >> s3;
    
    stringstream sss[] = { stringstream(s1), stringstream(s2), stringstream(s3) };
    
    for (int i = 0; i < 3; i++) {
        uint vtx, norm, uv;
        char slash;
        sss[i] >> vtx >> slash >> norm >> slash >> uv;
        
        pushInBuffer(resultOut->buffer, resultOut->vertices[vtx - INDICES_OFFSET]);
        pushInBuffer(resultOut->buffer, resultOut->normals[norm - INDICES_OFFSET]);
        pushInBuffer(resultOut->buffer, resultOut->uvs[uv - INDICES_OFFSET]);
    }
}
                                    
void WavefrontParser::pushInBuffer(vector<GLfloat>& vec, GLfloat first, GLfloat second) {
    vec.push_back(first);
    vec.push_back(second);
}

void WavefrontParser::pushInBuffer(vector<GLfloat>& vec, GLfloat first, GLfloat second, GLfloat third) {
    vec.push_back(first);
    vec.push_back(second);
    vec.push_back(third);
}

void WavefrontParser::pushInBuffer(vector<GLfloat>& vec, vec3 first) {
    vec.push_back(first.x);
    vec.push_back(first.y);
    vec.push_back(first.z);
}

void WavefrontParser::pushInBuffer(vector<GLfloat>& vec, vec2 first) {
    vec.push_back(first.x);
    vec.push_back(first.y);
}

