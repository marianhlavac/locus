#version 410 core
#define DIVIDE 4

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform float timeElapsed;
uniform uint tileDiv;
uniform float animSpeed;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUv;

void main() {
    mat4 mvp = P * V * M;
    gl_Position = mvp * vec4(position, 1);
    
    fragPos = vec3(M * vec4(position, 1));
    fragNormal = mat3(transpose(inverse(M))) * normal;
    fragUv = vec2(uv.x / DIVIDE, uv.y / DIVIDE);
    
    fragUv.x += (int(floor(timeElapsed * 2 * DIVIDE )) % DIVIDE) * (1.00/DIVIDE);
    fragUv.y += (int(floor(timeElapsed * 2)) % DIVIDE) * (1.00/DIVIDE);
}
