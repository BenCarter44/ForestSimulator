
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 transformMatrix;

void main()
{
    gl_Position = transformMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vColor = aColor;
}