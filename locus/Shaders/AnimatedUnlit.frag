#version 410 core
#define MAX_LIGHTS 8

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUv;

out vec4 color;

uniform sampler2D tex;

void main() {
    color = texture(tex, fragUv);
}
