//
//  WavefrontParser.hpp
//  locus
//
//  Created by Marián Hlaváč on 28/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef WavefrontParser_hpp
#define WavefrontParser_hpp

#include <vector>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include <GL/glew.h>

using namespace glm;
using namespace std;

struct WavefrontParserResult {
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<vec2> uvs;
    vector<GLfloat> buffer;
    vector<GLuint> indices;
};

class WavefrontParser {
public:
    static WavefrontParserResult* parse(const string& filename);
private:
    static void parseVertex(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseNormal(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseUV(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseFace(stringstream& ss, WavefrontParserResult* resultOut);
    static void pushInBuffer(vector<GLfloat>& vec, GLfloat first, GLfloat second);
    static void pushInBuffer(vector<GLfloat>& vec, GLfloat first, GLfloat second, GLfloat third);
    static void pushInBuffer(vector<GLfloat>& vec, vec3 first);
    static void pushInBuffer(vector<GLfloat>& vec, vec2 first);
};

#endif /* WavefrontParser_hpp */
