#version 330 core
out vec4 FragColor;
in vec4 fragmentColor;
uniform vec4 uniformFragmentColor;
in vec4 fragmentColor_updated;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
//   FragColor = vec4(0.3f,1.0f,1.0f,1.0f);
 FragColor = texture(ourTexture,TexCoord);
//FragColor = fragmentColor_updated;
//  FragColor = uniformFragmentColor;



}
