#version 410 core
#define MAX_LIGHTS 8

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUv;

uniform vec3 viewPos;

out vec4 color;

uniform sampler2D tex;

void main() {
    float fog = clamp(distance(fragPos, viewPos) / 50.0, 0.0, 1.0);
    
    color = mix(texture(tex, fragUv), vec4(0.1, 0.1, 0.1, 1), fog);
}
