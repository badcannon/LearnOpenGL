#version 330 core

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
in vec2 TexCoord;
out vec4 FragColor;

void main()
{
//    FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
    FragColor = texture(ourTexture,TexCoord);
}
