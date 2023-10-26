
#version 330 core
in vec3 WorldPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    // how much of the light will be factored into the ambient.
    vec3 ambient = ambientStrength * lightColor; 
    
    // diffuse.
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);  
    float diff = max(dot(norm, lightDir), 0.0);

    float brightness = 2.0;

    vec3 diffuse = diff * lightColor * brightness;
    vec3 result = (ambient + diffuse) * objectColor;

    float x = max(diff, 0.0);
    float y = max(diff, 0.0);
    float z = max(diff, 0.0);

    FragColor = vec4(result, 1.0);


}