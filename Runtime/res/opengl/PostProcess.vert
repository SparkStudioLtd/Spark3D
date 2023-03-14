#version 430 core
layout (location = 0) in vec3 UPosition;
layout (location = 1) in vec2 UTexCoord;
layout (location = 2) in vec3 UNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 fragPosLight;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = vec4(UPosition,1.0f);
    texCoord = UTexCoord;
    normal = mat3(transpose(inverse(model))) * UNormal;  
    fragPos = vec3(model * vec4(UPosition,1.0f));
    fragPosLight = lightSpaceMatrix * vec4(fragPos, 1.0f);
}