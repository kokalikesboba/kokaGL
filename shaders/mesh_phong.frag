#version 330 core
out vec4 FragColor;

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertUV;

uniform sampler2D diffuse0;

uniform vec3 cameraPos;
uniform vec3 lightColor;
uniform vec3 lightDirection;

void main()
{
    vec3 normal = normalize(vertNormal);
    vec3 lightDir = normalize(lightDirection);
    vec3 viewDir = normalize(cameraPos - vertPosition);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 ambient = vec3(0.07, 0.13, 0.17);

    float diffuse  = max(dot(normal, lightDir), 0.0);
    float specular = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    
    vec3 texColor = texture(diffuse0, vertUV).rgb;
    vec3 lit = texColor * (diffuse + ambient) + lightColor * specular;

    vec3 fogColor = vec3(0.6, 0.7, 0.8);
    float fogStart = 10.0; 
    float fogEnd   = 50.0;
    float dist = length(cameraPos - vertPosition);
    float fogAmt = clamp((dist - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    vec3 final = mix(lit, fogColor, fogAmt);

    FragColor = vec4(final, 1.0);
}