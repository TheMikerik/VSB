#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 frag_color;

// Material parameters
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

// Light struct
struct Light {
    vec3 lightPos;
    vec3 lightColor;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = 0.1 * texture(material.texture_diffuse1, TexCoords).rgb;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texture(material.texture_diffuse1, TexCoords).rgb;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * texture(material.texture_specular1, TexCoords).rgb;  
    
    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0);
}