#version 330 core
layout (location = 0) in vec3 aPos; // aPos layout for loc 0
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 aNormal; // aNormal layout for loc 2

out vec3 WorldPos; // Returns FragPos
out vec3 Normal; // Returns Normal

uniform mat4 model; // Receives model uniform
uniform mat4 view; // Receives view uniform
uniform mat4 projection; // Receives projection uniform

void main() {
    gl_Position = projection * view * model *  vec4(aPos, 1.0f);  // Implements transformations - multiplies transformation vectors
    WorldPos = vec3(model * vec4(aPos, 1.0));  // Sets fragment position
    
    Normal = aNormal;
}