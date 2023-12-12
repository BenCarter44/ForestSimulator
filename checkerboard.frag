#version 330 core
out vec4 FragColor; // Returns frag color

in vec3 Normal; // Takes in normal vec
in vec3 WorldPos; // Takes in fragpos vec

uniform vec3 lightPos; // Uniform loc for lightPos vec3
uniform vec3 viewPos; // Uniform loc for viewPos vec3
uniform vec3 lightColor; // Uniform loc for lightColor vec3
uniform vec3 squareColor; // Uniform loc for squareColor vec3


void main()
{
    float ambientStrength = 0.0;
    // how much of the light will be factored into the ambient.
    vec3 ambient = ambientStrength * lightColor; 
    
    // diffuse.
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);  
    float diff = max(dot(norm, lightDir), 0.0);

    float brightness = 1.0f;

    vec3 diffuse = diff * lightColor * brightness;
    
    // specular
    float specularStrength = 0.0f;
    vec3 viewDir = normalize(viewPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * squareColor;

    FragColor = vec4(squareColor, 1.0);


}
