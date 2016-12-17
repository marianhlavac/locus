#version 410 core

layout (location = 0) in vec3 position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 texCoords;

void main() {
    gl_Position = P * mat4(mat3(V)) * vec4(position, 1.0);
    texCoords = position;
}
