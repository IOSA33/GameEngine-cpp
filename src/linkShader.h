#include <glad/glad.h>
#include <GLFW/glfw3.h>

class LinkShader{
public:
    unsigned int shaderLinking(unsigned int vertexShader, unsigned int fragmentShader) {
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        return shaderProgram;
    }
};