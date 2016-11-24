#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
}
