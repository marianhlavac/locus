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

/// Result structure used in Wavefront parser output
struct WavefrontParserResult {
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<vec2> uvs;
    vector<vector<GLfloat>> bufferItems;
    vector<GLfloat> flatBuffer;
    vector<GLuint> indices;
};

/// Wavefront .obj files parser
class WavefrontParser {
public:
    static WavefrontParserResult* parse(const string& filename);
private:
    static void parseVertex(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseNormal(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseUV(stringstream& ss, WavefrontParserResult* resultOut);
    static void parseFace(stringstream& ss, WavefrontParserResult* resultOut);
    static vector<GLfloat> createBufferItem(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat s, GLfloat t);
    static long findOrInsertToBuffer(vector<GLfloat> bufferItem, WavefrontParserResult* resultOut);
};

#endif /* WavefrontParser_hpp */
