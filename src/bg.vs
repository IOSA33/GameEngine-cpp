#version 330 core
layout (location = 0) in vec3 aPos1;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord1; // the texture variable has attribute position 1

out vec2 TexCoord1;

void main()
{
    gl_Position = vec4(aPos1, 1.0);
    TexCoord1 = aTexCoord1;
}