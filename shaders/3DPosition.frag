
#version 330 core
out vec4 FragColor;

uniform vec4 mixColor; // we set this variable in OpenGL. IT MUST BE USED.


void main()
{
    FragColor = mixColor;
}