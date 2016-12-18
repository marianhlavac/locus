//
//  Mesh.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "WavefrontParser.hpp"

using namespace glm;

struct MeshVAO {
    MeshVAO() {
        glGenVertexArrays(1, &id);
    }
    void bind() {
        glBindVertexArray(id);
    }
    static void unbind() {
        glBindVertexArray(0);
    }
    GLuint id;
};

struct MeshVBO {
    MeshVBO(GLenum target, const GLvoid* data, GLsizeiptr size, GLenum usage) {
        glGenBuffers(1, &id);
        bind(target);
        glBufferData(target, size, data, usage);
    }
    void bind(GLenum target) {
        glBindBuffer(target, id);
    }
    void addAttrib(GLuint location, GLint size, GLenum type, GLsizei stride, int start) {
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, size, type, GL_FALSE, stride * sizeof(GLfloat), (void*)(start * sizeof(GL_FLOAT)));
    }
    void subData(GLenum target, const GLvoid* data, GLsizeiptr size) {
        bind(target);
        glBufferSubData(target, 0, size, data);
    }
    GLuint id;
};

class Mesh {
public:
    Mesh(WavefrontParserResult* parsed);
    Mesh(vector<GLfloat> buffer, GLuint bufferSize, vector<GLuint> indices, GLuint indicesSize);
    void draw();
    static Mesh* loadFromFile(const string & filename);
    static Mesh* createCube(float size);
    static Mesh* createQuad(vec2 size);
    void addAttrib(GLuint location, GLint size, GLenum type, GLsizei stride, int start);
private:
    void createBuffer(GLuint* vbo, unsigned length, const GLvoid * data, GLenum target);
    MeshVBO* verticesVbo;
    MeshVBO* indicesVbo;
    MeshVAO* vao;
    long vertexCount;
    long triangleCount;
};

#endif /* Mesh_hpp */
