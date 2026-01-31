#version 330 core
out vec4 FragColor;

in vec3 crntPosition;
in vec3 vertexNormal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec3 cameraPos;

void main()
{
    vec3 lightColor   = vec3(1.0, 1.0, 1.0);
    vec3 lightDirection = vec3(1.0, 1.0, 1.0);
    vec3 ambientLight = vec3(0.4, 0.4, 0.4);

    // Base color
    vec3 baseColor = texture(diffuse0,texCoord).rgb; 
    vec3 ambientComponent = baseColor * ambientLight;

    // Diffuse
    vec3 lightDirectionNormalized = normalize(lightDirection);
    vec3 vertexNormalNormalized = normalize(vertexNormal);
    float diffuseScalar = max(dot(vertexNormalNormalized, -lightDirectionNormalized), 0.0);
    vec3 diffuseComponent = baseColor * lightColor * diffuseScalar;

    // Specular
        

    vec3 combinedColor = ambientComponent + diffuseComponent;
    FragColor = vec4(combinedColor, 1.0);
}
  