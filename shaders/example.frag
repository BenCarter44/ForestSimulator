
#version 330 core
out vec4 FragColor;

uniform vec4 outColor; // we set this variable in OpenGL. IT MUST BE USED.

void main()
{
    vec4 temp = vec4(0.0f, 0.1f, 1.0f, 1.0f);
    FragColor = normalize(temp + outColor);
} 