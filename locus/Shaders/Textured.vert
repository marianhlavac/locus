#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUv;

void main() {
    mat4 mvp = P * V * M;
    gl_Position = mvp * vec4(position, 1);
    
    fragPos = vec3(M * vec4(position, 1));
    fragNormal = normal;
    fragUv = vec2(uv.x, 1 - uv.y);
}
