#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;

out vec3 fragPos;
out vec3 fragNormal;

void main() {
    gl_Position = mvp * vec4(position, 1);
    
    fragPos = vec3(m * vec4(position, 1));
    fragNormal = normal;
}
