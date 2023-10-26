
#version 330 core
in vec3 WorldPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    float ambientStrength = 0.1;
    // how much of the light will be factored into the ambient.
    vec3 ambient = ambientStrength * lightColor; 
    
    // diffuse.
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);  
    float diff = max(dot(norm, lightDir), 0.0);

    float brightness = 0.5;

    vec3 diffuse = diff * lightColor * brightness;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);


}