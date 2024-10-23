#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
    
    ex_worldPosition = vec3(modelMatrix * vec4(in_Position, 1.0));
  
    ex_worldNormal = mat3(transpose(inverse(modelMatrix))) * in_Normal;
}