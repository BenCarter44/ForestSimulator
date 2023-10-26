#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 WorldPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    Normal = aNormal;

    // we want the world space coordinate.
    WorldPos = vec3(model * vec4(aPos, 1.0));
}