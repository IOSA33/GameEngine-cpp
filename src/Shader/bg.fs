#version 330 core
out vec4 FragColor1;  

in vec2 TexCoord1;

uniform sampler2D background;

void main()
{
    FragColor1 = texture(background, TexCoord1);
}