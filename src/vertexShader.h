#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexShader {
public:
    unsigned int buildAndCompileVertexShader(const char* vertexShaderSource) {
        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        return vertexShader;
    }
};