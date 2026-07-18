#version 410 core

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertUV;

uniform sampler2D baseColor;

layout (std140) uniform viewportUBO {
    mat4 viewportMatrix;
    mat4 viewportOrientation;
    vec3 viewportPosition;
    float pad0;
};

layout (std140) uniform lightUBO {
    vec4 color0;
    vec3 direction0;
    float padding0;
};

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(vertNormal);
    vec3 lightDir = normalize(direction0);
    vec3 viewDir = normalize(viewportPosition - vertPosition);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 ambient = vec3(0.4, 0.4, 0.4);

    float diffuse  = max(dot(normal, lightDir), 0.0);
    float specular = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    
    vec3 texColor = texture(baseColor, vertUV).rgb;
    vec3 lit = texColor * (diffuse + ambient) + vec3(color0.x, color0.y, color0.z) * specular;

    vec3 fogColor = vec3(0.07, 0.13, 0.17);
    float fogStart = 5.0; 
    float fogEnd   = 40.0;
    float dist = length(viewportPosition - vertPosition);
    float fogAmt = clamp((dist - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    vec3 final = mix(lit, fogColor, fogAmt);

    FragColor = vec4(final, 1.0);
}