#version 430 core
layout (location = 0) in vec3 UPosition;
layout (location = 1) in vec2 UTexCoord;
layout (location = 2) in vec3 UNormal;


uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(UPosition, 1.0);
}