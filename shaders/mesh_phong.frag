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
    vec3 ambientLight = vec3(0.4, 0.4, 0.4);

    // Base color
    vec3 baseColor = texture(diffuse0,vertUV).rgb; 
    vec3 ambientComponent = baseColor * ambientLight;

    // Diffuse
    vec3 lightDirectionNormalized = normalize(lightDirection);
    vec3 vertNormalNormalized = normalize(vertNormal);
    float diffuseScalar = max(dot(vertNormalNormalized, lightDirectionNormalized), 0.0);
    vec3 diffuseComponent = baseColor * lightColor * diffuseScalar;

    vec3 combinedColor = ambientComponent + diffuseComponent;
    FragColor = vec4(combinedColor, 1.0);
    // FragColor = vec4(vertNormalNormalized * 0.5 + 0.5, 1.0);
}
  