
#version 330 core
out vec4 FragColor; // Returns FragColor

in vec2 texCoord; // Receives FragPos

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform vec2 decision;

void main()
{
    vec4 FragColorA = texture(ourTexture, texCoord);
    vec4 FragColorB = texture(ourTexture2, texCoord);

    FragColor = decision.x * FragColorA + decision.y * FragColorB;

    // FragColor = vec4(texCoord.x, texCoord.y, 0.0, 0.0);
}
