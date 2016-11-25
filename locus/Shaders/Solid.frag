#version 410 core

uniform vec3 lightPos;

in vec3 fragPos;
in vec3 fragNormal;

out vec4 color;

void main() {
    vec3 ambientColor = vec3(0.15f, 0.165f, 0.18f);
    vec3 diffuseColor = vec3(0.9f, 0.9f, 0.9f);
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;
    
    color = vec4(ambientColor + diffuse, 1.0);
}
