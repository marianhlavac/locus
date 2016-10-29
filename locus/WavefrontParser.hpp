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
    vector<GLfloat> vertices;
    vector<GLfloat> normals;
    vector<GLfloat> uvs;
    vector<GLuint> vertexIndices;
    vector<GLuint> normalIndices;
    vector<GLuint> uvIndices;
};

class WavefrontParser {
public:
    static WavefrontParserResult* parse(const string& filename);
private:
    static void parseVertex(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseNormal(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseUV(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseFace(stringstream& ss, WavefrontParserResult* resultOut);
};

#endif /* WavefrontParser_hpp */
