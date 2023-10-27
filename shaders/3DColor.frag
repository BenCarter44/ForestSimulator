
#version 330 core
in vec3 WorldPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightSettings;

void main()
{
    float ambientStrength = lightSettings.x;
    // how much of the light will be factored into the ambient.
    vec3 ambient = ambientStrength * lightColor; 
    
    // diffuse.
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);  
    float diff = max(dot(norm, lightDir), 0.0);

    float brightness = lightSettings.y;

    vec3 diffuse = diff * lightColor * brightness;
    
    // specular
    float specularStrength = lightSettings.z;
    vec3 viewDir = normalize(camPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), lightSettings.w);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);


}