#version 330 core
layout (location = 0) in vec3 aPos; // Receives aPos
layout (location = 1) in vec2 aTexCoord; // Receives aNormal

out vec3 FragPos; // Returns FragPos
out vec2 texCoord; // Returns Normal

uniform mat4 model; // Receives model uniform
uniform mat4 view; // Receives view uniform
uniform mat4 projection; // Receives projection uniform
uniform vec2 decision;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0f);  // Implements transformations - multiplies transformation vectors
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // texCoord = vec2(atan(aPos.x,aPos.y), atan(aPos.x,aPos.z));
    

    

    // texCoord = vec2(aPos.x / 2.0, 0.0);
    vec2 texCoordA = vec2(aPos.x / 2.0, 1.0 - ((aPos.y - 0.75) * 1.75)); 
    vec2 texCoordB = vec2((aTexCoord.x * 0.5 + 0.5), 1.0 - (aTexCoord.y * 0.5 + 0.5));

    texCoord = vec2(decision.x * texCoordA.x + decision.y * texCoordB.x,  decision.x * texCoordA.y + decision.y * texCoordB.y);

    // texCoord 
}

