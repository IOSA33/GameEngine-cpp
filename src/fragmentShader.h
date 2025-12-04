#include <glad/glad.h>
#include <GLFW/glfw3.h>

class FragmentShader {
public: 
    FragmentShader() = default;

    unsigned int fragmentShaderCompile(const char* fragmentShaderSource) {
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	    glCompileShader(fragmentShader);
        return fragmentShader;
    }
};