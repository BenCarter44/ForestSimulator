
#version 330 core
out vec4 FragColor;

in vec3 vColor;

uniform vec4 mixColor; // we set this variable in OpenGL. IT MUST BE USED.


void main()
{
    vec4 oc = vec4(vColor, 1.0);
    FragColor = normalize(oc + mixColor);
} 