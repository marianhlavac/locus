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
    
    while (getline(file, line)) {
        stringstream ss(line);
        
        string type;
        ss >> type;
        
        if (type == "v") parseVertex(ss, result);
        if (type == "vt") parseUV(ss, result);
        if (type == "vn") parseNormal(ss, result);
        if (type == "f") parseFace(ss, result);
    }

    return result;
}

void WavefrontParser::parseVertex(stringstream& ss, WavefrontParserResult* resultOut) {
    for (int i = 0; i < 3; i++) {
        float val;
        ss >> val;
        
        resultOut->vertices.push_back(val);
    }
}

void WavefrontParser::parseNormal(stringstream& ss, WavefrontParserResult* resultOut) {
    for (int i = 0; i < 3; i++) {
        float val;
        ss >> val;
        
        resultOut->normals.push_back(val);
    }
}

void WavefrontParser::parseUV(stringstream& ss, WavefrontParserResult* resultOut) {
    for (int i = 0; i < 2; i++) {
        float val;
        ss >> val;
        
        resultOut->uvs.push_back(val);
    }
}

void WavefrontParser::parseFace(stringstream& ss, WavefrontParserResult* resultOut) {
    string s1, s2, s3;
    ss >> s1 >> s2 >> s3;
    
    stringstream sss[] = { stringstream(s1), stringstream(s2), stringstream(s3) };
    
    for (int i = 0; i < 3; i++) {
        uint vtx, norm, uv;
        sss[i] >> vtx >> norm >> uv;
        
        resultOut->vertexIndices.push_back(vtx - INDICES_OFFSET);
        resultOut->normalIndices.push_back(norm - INDICES_OFFSET);
        resultOut->uvIndices.push_back(uv - INDICES_OFFSET);
    }
}
