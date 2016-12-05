#version 410 core
#define MAX_LIGHTS 8

struct DirectionalLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 fragNormal;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform DirectionalLight directionalLights[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];

uniform uint directionalLightsCount;
uniform uint pointLightsCount;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    
    return light.ambient + diff * light.diffuse + spec * light.specular;
}

vec3 CalcPointLight(PointLight light, vec3 position, vec3 normal, vec3 view) {
    vec3 lightDir = normalize(light.position - position);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    
    float dist = length(light.position - position);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    return attenuation * (light.ambient + diff * light.diffuse + spec * light.specular);
}

void main() {
    vec3 norm = normalize(fragNormal);
    
    vec3 result = vec3(0);
    
    for (int i = 0; i < pointLightsCount; i++) {
        result += CalcPointLight(pointLights[i], fragPos, norm, viewPos);
    }
    
    for (int i = 0; i < directionalLightsCount; i++) {
        result += CalcDirectionalLight(directionalLights[i], norm, viewPos);
    }
    
    color = vec4(result, 1);
}
