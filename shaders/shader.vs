#version 330 core
layout (location = 0 ) in vec3 aPos;
layout (location = 1 ) in vec3 aColor;
out vec4 fragmentColor; //Fragment color input from the vertex shader!
void main()
{
   gl_Position = vec4(aPos,1.0f);
// fragmentColor = vec4(0.5f,0.0f,0.5f,1.0f);
   fragmentColor = vec4(aColor,1.0f);
};
