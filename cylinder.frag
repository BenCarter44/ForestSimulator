#version 330 core
out vec4 FragColor; // Returns FragColor

in vec3 Normal; // Receives Normal
in vec3 FragPos; // Receives FragPos
  
uniform vec3 lightPos; // Receives lightPos uniform
uniform vec3 viewPos; // Receives viewPos uniform
uniform vec3 lightColor; // Recieves lightColor uniform
uniform vec3 cylinderColor; // Receives cylinderColor uniform

void main()
{
    // ambient
    float ambientStrength = 0.8;  // Set ambient strength
    vec3 ambient = ambientStrength * lightColor;  // Sets ambient - multiplies strength decimal by light color
  	
    // diffuse 
    vec3 norm = normalize(Normal);  // Normalizes normal
    vec3 lightDir = normalize(lightPos - FragPos);  // Sets light direction based on light - frag position
    float diff = max(dot(norm, lightDir), 0.0);  // Diff value based on max method and dot product
    vec3 diffuse = diff * lightColor;  // Sets diffuse
    
    // specular
    float specularStrength = 0.25f;  // Sets specular strength
    vec3 viewDir = normalize(viewPos - FragPos);  // Sets view direction
    vec3 reflectDir = reflect(-lightDir, norm);  // Sets reflect direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);  // Sets specular based on power, max, and dot product
    vec3 specular = specularStrength * spec * lightColor;  // Sets specular
        
    vec3 result = (ambient + diffuse + specular) * cylinderColor;  // Adds ambient, diffuse, and specular and multiplies by wall color
    FragColor = vec4(result, 1.0f);  // Sets vec4 based on result
} 
