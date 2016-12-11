#version 410 core

in vec2 texPos;

out vec4 color;

uniform sampler2D tex;

void main() {
    color = texture(tex, texPos);
}
