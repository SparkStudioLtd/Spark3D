#version 430 core
layout (location = 0) in vec3 UPosition;
layout (location = 1) in vec2 UTexCoord;
layout (location = 2) in vec3 UNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 fragPosLight;



void main()
{
    gl_Position = vec4(UPosition,1.0f);
    texCoord = UTexCoord;
    normal = vec3(0,0,0);
    fragPos = vec3(0,0,0);
    fragPosLight = vec4(0,0,0,0);
}