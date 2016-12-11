#version 410 core

in vec3 fragPos;

uniform uint selectionId = 0;

out vec4 color;

void main() {
    color = vec4(selectionId / 256.0, selectionId / 256.0, selectionId / 256.0, 1.0);
}
