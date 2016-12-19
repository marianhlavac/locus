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

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUv;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D tex;
uniform sampler2D specmap;
uniform bool hasSpecmap;
uniform DirectionalLight directionalLights[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];

uniform uint directionalLightsCount;
uniform uint pointLightsCount;
uniform uint spotLightsCount;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0);
    
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 h = normalize(lightDir + viewDir);
        spec = pow(max(dot(h, normal), 0.0), 32);
    }
    
    if (hasSpecmap) { spec *= texture(specmap, fragUv).r; }
    
    return light.ambient + diff * light.diffuse + spec * light.specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 h = normalize(lightDir + viewDir);
        spec = pow(max(dot(h, normal), 0.0), 32);
    }
    
    float dist = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    if (hasSpecmap) { spec *= texture(specmap, fragUv).r; }
    
    return attenuation * (light.ambient + diff * light.diffuse + spec * light.specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 h = normalize(lightDir + viewDir);
        spec = pow(max(dot(h, normal), 0.0), 32);
    }
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    float dist = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    if (hasSpecmap) { spec *= texture(specmap, fragUv).r; }
    
    return attenuation * intensity * (light.ambient + diff * light.diffuse + spec * light.specular);
}

void main() {
    vec3 norm = normalize(fragNormal);
    
    vec3 result = vec3(0);
    
    for (int i = 0; i < pointLightsCount; i++) {
        result += CalcPointLight(pointLights[i], norm);
    }
    
    for (int i = 0; i < directionalLightsCount; i++) {
        result += CalcDirectionalLight(directionalLights[i], norm);
    }
    
    for (int i = 0; i < spotLightsCount; i++) {
        result += CalcSpotLight(spotLights[i], norm);
    }
    
    float fog = clamp(distance(fragPos, viewPos) / 50.0, 0.0, 1.0);
    
    color = mix(texture(tex, fragUv) * vec4(result, 1), vec4(0.1, 0.1, 0.1, 1), fog);
}
