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
    
    // Flatten buffer
    for (vector<GLfloat> bufferItem : result->bufferItems) {
        result->flatBuffer.insert(result->flatBuffer.end(), bufferItem.begin(), bufferItem.end());
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
        int vtxid = -1, normid = -1, uvid = -1;
        char slash;
        sss[i] >> vtxid >> slash >> uvid >> slash >> normid;
        
        vec3 vtx(0), norm(0);
        vec2 uv(0);
        
        if (vtxid > 0) vtx = resultOut->vertices[vtxid - 1];
        if (uvid > 0) uv = resultOut->uvs[uvid - 1];
        if (normid > 0) norm = resultOut->normals[normid - 1];
        
        vector<GLfloat> bufferItem = createBufferItem(vtx.x, vtx.y, vtx.z, norm.x, norm.y, norm.z, uv.s, uv.t);
        
        resultOut->indices.push_back((GLuint)findOrInsertToBuffer(bufferItem, resultOut));
    }
}

vector<GLfloat> WavefrontParser::createBufferItem(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat s, GLfloat t) {
    vector<GLfloat> item = {
        x, y, z, nx, ny, nz, s, t
    };
    return item;
}
                                    
long WavefrontParser::findOrInsertToBuffer(vector<GLfloat> bufferItem, WavefrontParserResult *resultOut) {
    auto result = find_if(resultOut->bufferItems.begin(), resultOut->bufferItems.end(), [&] (const vector<GLfloat> i) {
        return i == bufferItem;
    });
    
    if (result == resultOut->bufferItems.end()) {
        resultOut->bufferItems.push_back(bufferItem);
        return std::distance(resultOut->bufferItems.begin(), resultOut->bufferItems.end()) - 1;
    } else {
        return std::distance(resultOut->bufferItems.begin(), result);
    }
}

