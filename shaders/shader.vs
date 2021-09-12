#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
out vec4 fragmentColor; // fragmentColor input for the fragment shader
uniform float uniformOffset; //offset
out vec4 fragmentColor_updated;
out vec2 TexCoord;
void main()
{
 //upside down triangle
// gl_Position = vec4(aPos.x + uniformOffset,-aPos.y,aPos.z,1.0f);
 gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0f);
 //gl_Position = vec4(aPos,1.0f);
 //fragmentColor = vec4(0.5f,0.5f,0.5f,1.0f);
 fragmentColor = vec4(aColor,1.0f);
// fragmentColor_updated = gl_Position;

//Texture
TexCoord = aTexCoords;
}
