#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 position_world;
out vec3 normal_camera;
out vec3 eye_camera;
out vec3 light_camera;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    
    position_world = (m * vec4(position, 1.0)).xyz;
    
    vec3 vertex_camera = (v * m * vec4(position, 1.0)).xyz;
    eye_camera = vec3(0,0,0) - vertex_camera;
    
    vec3 lightpos_camera = (v * vec4(0, 0, -1.0, 1.0)).xyz;
    light_camera = lightpos_camera + eye_camera;
    
    normal_camera = (v * m * vec4(normal, 1.0)).xyz;
}
