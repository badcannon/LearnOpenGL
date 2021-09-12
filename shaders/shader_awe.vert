#version 330 core


layout (location = 2) in vec2 aTexCoord;
layout (location = 1) in vec3 aColor;
layout (location = 0) in vec3 aPos;
uniform float uniformOffsetx;
uniform float uniformOffsety;
out vec2 TexCoord;

void main(void)
{
    gl_Position = vec4(aPos.x+uniformOffsetx,aPos.y + uniformOffsety,aPos.z,1.0f);
    TexCoord = aTexCoord;
}
