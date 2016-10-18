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

#include "Material.hpp"

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
    MeshVBO(GLenum target, const GLvoid* data, GLsizeiptr size) {
        glGenBuffers(1, &id);
        bind(target);
        glBufferData(target, size, data, GL_STATIC_DRAW);
    }
    void bind(GLenum target) {
        glBindBuffer(target, id);
    }
    void addAttrib(GLuint location, GLint size, GLenum type, GLsizei stride, const GLvoid* ptr) {
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, size, type, GL_FALSE, stride, ptr);
    }
    GLuint id;
};

class Mesh {
public:
    Mesh(Material* mat);
    void draw();
private:
    void createBuffer(GLuint* vbo, unsigned length, const GLvoid * data, GLenum target);
    Material* material;
    MeshVBO* verticesVbo;
    MeshVBO* indicesVbo;
    MeshVAO* vao;
};

#endif /* Mesh_hpp */
