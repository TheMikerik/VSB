// phong_fragment_shader_multiple.glsl
#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 viewPos;
uniform vec3 lightPos[10];  // Array of light positions for 10 lights
uniform vec3 lightColor[10]; // Array of light colors for 10 lights
uniform int numLights;       // Number of lights to process

void main()
{
    vec3 ambient = vec3(0.1);  // Base ambient light intensity
    vec3 result = vec3(0.0);   // Accumulator for all lighting effects

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        
        // Ambient component
        vec3 ambientComp = ambient * lightColor[i];

        // Diffuse component
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i];

        // Specular component
        float specularStrength = 0.5;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor[i];

        // Accumulate lighting effects for each light
        result += (ambientComp + diffuse + specular);
    }
    
    frag_colour = vec4(result, 1.0);
}
