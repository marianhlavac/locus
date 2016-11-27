#version 410 core

uniform vec3 lightPos;
uniform sampler2D tex;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUv;

out vec4 color;

void main() {
    vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);
    vec3 diffuseColor = vec3(0.9f, 0.9f, 0.9f);
    vec3 specularColor = vec3(0.4f, 0.4f, 0.4f);
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = lightPos;
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularColor * spec;
    
    color = texture(tex, fragUv) * vec4(ambientColor + diffuse + specular, 1.0);
}
