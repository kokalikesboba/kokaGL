#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
    // Hardcoded sun + fake camera
    vec3 sunDir = normalize(vec3(0.0, 1.0, 0.0));   // sun above
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));  // fake camera forward

    vec3 lightColor = vec3(1.0);
    float ambient = 0.25;

    vec3 N = normalize(Normal);

    // ---- Diffuse ----
    vec3 L = normalize(-sunDir); // light rays go down
    float diff = max(dot(N, L), 0.0);

    // ---- Specular (Phong) ----
    vec3 R = reflect(-L, N);
    float specPower = 16.0; // hardness
    float specFactor = pow(max(dot(viewDir, R), 0.0), specPower);

    // Specular map (single channel)
    float specMap = texture(specular0, texCoord).r;

    // ---- Final color ----
    vec3 albedo = texture(diffuse0, texCoord).rgb;

    vec3 color =
        albedo * (ambient + diff) +
        specMap * specFactor * lightColor * 0.5;

    FragColor = vec4(color, 1.0);
}
