#version 330 core
out vec4 FragColor; // Returns frag color

in vec3 Normal; // Takes in normal vec
in vec3 FragPos; // Takes in fragpos vec

uniform vec3 lightPos; // Uniform loc for lightPos vec3
uniform vec3 viewPos; // Uniform loc for viewPos vec3
uniform vec3 lightColor; // Uniform loc for lightColor vec3
uniform vec3 squareColor; // Uniform loc for squareColor vec3

void main() {
    // ambient
    float ambientStrengh = 0.8; // Set ambient strength
    vec3 ambient = ambientStrengh * lightColor; // Sets ambient
    
    // diffuse
    vec3 norm = normalize(Normal); // Normalizes normal
    vec3 lightDir = normalize(lightPos - FragPos); // Sets lightDir
    float diff = max(dot(norm, lightDir), 0.0); // Gets diff with dot product
    vec3 diffuse = diff * lightColor; // Sets diffuse

    // specular
    float specularStrength = 0.25f; // Sets specularStrength
    vec3 viewDir = normalize(viewPos - FragPos); // Gets viewDir
    vec3 reflectDir = reflect(-lightDir, norm); // Gets reflectDir
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8); // Gets spec with dot product
    vec3 specular = specularStrength * spec * lightColor; // Sets specular

    vec3 result = (ambient + diffuse + specular) * squareColor; // Calculates result
    FragColor = vec4(result, 1.0f); // Sets fragcolor output
}
