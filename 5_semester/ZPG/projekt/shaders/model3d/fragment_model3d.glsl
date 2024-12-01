#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

// Material parameters
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    sampler2D texture_height1;
}; 

uniform Material material;

// Lighting parameters
struct Light {
    vec3 position;
    vec3 color;
};

uniform Light light;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = 0.1 * light.color;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * light.color;  
    
    // Texture
    vec4 texColor = texture(material.texture_diffuse1, TexCoords);
    if(texColor.a < 0.1)
        discard;

    vec3 result = (ambient + diffuse + specular) * texColor.rgb;
    FragColor = vec4(result, 1.0);
}