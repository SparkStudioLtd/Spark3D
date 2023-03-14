#version 430 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 EmissionColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 fragPosLight;

uniform sampler2D texSampler;
uniform sampler2D depthMap;
uniform bool useTexture;
uniform vec3 albedoColor;
uniform bool useLighting;

uniform vec3 lightColor;
uniform vec3 lightDire;
uniform vec3 eyePos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, normalize(lightDire - fragPos))), 0.005);  
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    //return shadow;
    return 1.0f;
}

vec3 lightCalulcations(vec3 objectColor) {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightDire - fragPos);
    vec3 viewDir = normalize(eyePos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    //float shadow = ShadowCalculation(fragPosLight);
    //vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    return result;
}

void main()
{
    vec3 result = vec3(0.0f);
    float alpha = 1.0f;
    if(useTexture)
    {
        vec4 texelResult = texture(texSampler,texCoord);
        float texAlpha = texelResult.w;
        result += texelResult.rgb;
        alpha = texAlpha;
    } else {
        result += albedoColor;
    }

    if(useLighting)
        result = lightCalulcations(result);

    //discard;
    FragColor = vec4(result,alpha);
    EmissionColor = vec4(result,alpha);
} 