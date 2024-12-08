#version 330 core

in vec3 worldNormal;
in vec3 worldPosition;
in vec2 TexCoord;
in vec3 FragPos;

uniform vec3 spotDir;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform bool hasTexture;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

uniform vec3 lightColor[30];
uniform vec3 lightPositions[30];
uniform int numLights;

out vec4 fragColor;

void main() {
    vec3 camVector = normalize(viewPos - worldPosition);
    vec3 norm = normalize(worldNormal);
    
    vec3 result = vec3(0.0);
    
    for (int i = 0; i < numLights; ++i) {
        vec3 lightVector = normalize(lightPositions[i] - worldPosition);
        vec3 reflectVector = reflect(-lightVector, norm);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * materialAmbient * lightColor[i];

        float diff = max(dot(norm, lightVector), 0.0);
        vec3 diffuse = materialDiffuse * diff * lightColor[i];

        float specularStrength = 0.5;
        float spec = pow(max(dot(reflectVector, camVector), 0.0), materialShininess);
        vec3 specular = specularStrength * spec * materialSpecular * lightColor[i];

        result += (ambient + diffuse + specular);
    }
    
    vec3 textureColor = hasTexture ? texture(texture_diffuse1, TexCoord).rgb : vec3(1.0);
    fragColor = vec4(result * textureColor, 1.0);
}