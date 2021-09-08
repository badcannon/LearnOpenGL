#version 330 core
out vec4 FragColor;
in vec4 fragmentColor;
uniform vec4 uniformFragmentColor;
void main()
{
//   FragColor = vec4(0.3f,1.0f,1.0f,1.0f);
 FragColor = fragmentColor;\n
//  FragColor = uniformFragmentColor;
};
