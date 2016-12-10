#version 410 core

in vec2 texPos;

out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texPos).r);
    color = vec4(textColor, 1.0) * sampled;
}
