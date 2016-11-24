#version 410 core

in vec3 position_world;
in vec3 normal_camera;
in vec3 light_camera;

out vec4 color;

void main() {
    
    vec3 n = normalize(normal_camera);
    vec3 l = normalize(light_camera);
    
    float cosTheta = clamp(dot(n, l), 0, 1);
    
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * cosTheta + vec4(0.1f, 0.1f, 0.1f, 1.0f);
}
