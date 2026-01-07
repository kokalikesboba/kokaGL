#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;



// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
    // 1. Calculate the Model Matrix by combining TRS
    // Note: We remove the '-' from rotation and the 'model' uniform (since it's identity anyway)
    mat4 modelMatrix = translation * rotation * scale;
    
    // 2. Calculate current world position
    crntPos = vec3(modelMatrix * vec4(aPos, 1.0f));
    
    // 3. Assign attributes
    Normal = aNormal;
    color = aColor;
    texCoord = aTex; // Keep it simple for the sanity check
    
    // 4. Final screen position
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}