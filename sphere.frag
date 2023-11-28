#version 330 core
out vec4 FragColor; // Returns FragColor

in vec3 Normal; // Receives normal
in vec3 FragPos; // Receives FragPos

uniform vec3 lightPos; // Receives lightPos uniform
uniform vec3 viewPos; // Receives viewPos uniform
uniform vec3 lightColor; // Receives lightColor uniform
uniform vec3 sphereColor; // Receives sphereColor uniform

void main() {
    // ambient
    float ambientStrengh = 0.8; // Set ambient strength
    vec3 ambient = ambientStrengh * lightColor; // Sets ambient
    
    // diffuse
    vec3 norm = normalize(Normal); // Normalizes normal
    vec3 lightDir = normalize(lightPos - FragPos); // Gets lightDir
    float diff = max(dot(norm, lightDir), 0.0); // Gets diff
    vec3 diffuse = diff * lightColor; // Sets diffuse

    // specular
    float specularStrength = 0.25f; // Sets specularStrength
    vec3 viewDir = normalize(viewPos - FragPos); // Get viewDir
    vec3 reflectDir = reflect(-lightDir, norm); // Get reflectDir
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8); // Get spec
    vec3 specular = specularStrength * spec * lightColor; // Set specular

    vec3 result = (ambient + diffuse + specular) * sphereColor; // Calculate result
    FragColor = vec4(result, 1.0f); // Set FragColor output
}
