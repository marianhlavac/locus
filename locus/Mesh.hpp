//
//  Mesh.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <SFML/OpenGL.hpp>
#include <OpenGL/gl3.h>
#include <string>

struct MeshVAO {
    MeshVAO() {
        glGenVertexArrays(1, &id);
    }
    void bind() {
        glBindVertexArray(id);
    }
    GLuint id;
};

struct MeshVBO {
    MeshVBO(GLenum target, const GLvoid* data, GLsizeiptr size) {
        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, size, data, GL_STATIC_DRAW);
    }
    void bind(GLenum target) {
        glBindBuffer(target, id);
    }
    GLuint id;
};

class Mesh {
public:
    Mesh();
    void draw();
private:
    void createBuffer(GLuint* vbo, unsigned length, const GLvoid * data, GLenum target);
    MeshVBO* verticesVbo;
    MeshVBO* indicesVbo;
    MeshVAO* vao;
};

#endif /* Mesh_hpp */
