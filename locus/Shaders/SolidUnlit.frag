#version 410 core
#define MAX_LIGHTS 8

in vec3 fragPos;
in vec3 fragNormal;

out vec4 color;

void main() {
    vec3 normal = normalize(fragNormal);
    
    vec3 result = vec3(0);
    
    vec3 lightDir = normalize(vec3(-0.5, 1, -0.5));
    vec3 reflectDir = reflect(-lightDir, normal);
    
    float diff = max(dot(normal, lightDir), 0);
    
    result += 0.1 + diff * 1.0;

    
    color = vec4(result, 1);
}
