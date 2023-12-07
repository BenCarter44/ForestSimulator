#version 330 core
layout (location = 0) in vec3 aPos; // Receives aPos
layout (location = 1) in vec2 aTexCoord; // Receives aNormal

out vec3 FragPos; // Returns FragPos
out vec2 texCoord; // Returns Normal

uniform mat4 model; // Receives model uniform
uniform mat4 view; // Receives view uniform
uniform mat4 projection; // Receives projection uniform

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0f);  // Implements transformations - multiplies transformation vectors
    texCoord = vec2(1.0 - aTexCoord.x, aTexCoord.y);

}
