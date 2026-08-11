#version 410 core

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertUV;

uniform sampler2D baseColor;
uniform sampler2D orm;
uniform sampler2D normal;

layout (std140) uniform viewportUBO {
    mat4 viewportMatrix;
    mat4 viewportOrientation;
    vec3 viewportPosition;
};

struct Light {
    vec4 color;
    vec3 position;
    int  pad;
    vec3 direction;
    int  type;
};

layout (std140) uniform lightUBO {
    Light lights[4];
};

out vec4 FragColor;

#define PI 3.1415927

// Normalized normal distribution function
// D = a^2 / PI * (dot(normal, half)^2 * (a^2-1)+1)^2
float NormalDistrbution(float hv, float a) {
    float a2 = a * a;
    float denom = hv * hv * (a2 - 1.0) + 1.0;
    return a2 / (PI * denom * denom);
}

// Geometry function approximating self shadowing
// calculated twice for view vector and light direction 
// G = dot(normal,view)/dot(normal,view)*(1-k) + k 
float SelfShadowing(float hv, float nv, float k) {
    return nv / nv * (1-k) + k
}



void main()
{

    // vec3 FinalColor - (DiffuseBSDF + SpecularBRDF) * LightIntensity * nDotL;

    //  Didirection reflecance distirbution function
    // Cook torrance BRDF
    // kD * fLambert / PI; 
    // kS * fCookTorrance
    // kD + kS = 1

    // Normal Distribution fuctnion
    // Geometry function
    // Fresnel function
    // SpecularBRDF = D * G * F / 4 * dot(normal, light) * dot(normal, view)

    // Fresnel function
    // F_0 + (1-F_0) * (1 - dot(view,half))^5

}