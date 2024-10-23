#version 330 core

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main(void) {
    vec3 lightVector = normalize(lightPosition - ex_worldPosition);
    float diff = max(dot(ex_worldNormal, lightVector), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = ambientColor;
    vec3 result = ambient + diffuse;
    
    out_Color = vec4(result, 1.0);
}