#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "src/shader.h"
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "src/stb_image.h"
#include "src/gameClasses/Player.h"
#include "src/gameClasses/Weapon.h"
#include "src/gameClasses/Pistol.h"
#include "src/gameClasses/FireSword.h"
#include "src/gameClasses/MathLine.h"
#include <vector>
#include <algorithm>

// declaration
void processInput(GLFWwindow *window, std::vector<Player>& vecPlayers, Shader& shader, GLfloat deltaTime, std::vector<Weapon>& vec,  std::vector<Pistol>& pistol);
void setVisible(float& x, char c);

namespace Globals {
    float visible = 0.2f;
} // namespace Globals

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// settings
constexpr unsigned int SCR_WIDTH = 900;
constexpr unsigned int SCR_HEIGHT = 900;
//constexpr unsigned int SCR_HEIGHT = SCR_WIDTH * 9 / 16 + 60;

void setVisible(float& x, char c) {
	const std::string op = "main/setVisible()";
	switch (c)
	{
	case 'u':
        if (!(x > 1.0)) {
            x += 0.02f;
        }
		break;
	case 'd':
		if (!(x < 0.0)) {
            x -= 0.02f;
        }
		break;
	default:
		std::cout << op << ": default break\n";
		break;
	}
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../src/shader.vs", "../src/shader.fs"); // you can name your shader files however you like
    Shader bgShader("../src/bg.vs", "../src/bg.fs");
    Shader line("../src/line.vs", "../src/line.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
        0.1f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.1f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float verticesBG[] = {
        // positions         // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indicesBG[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float verticesLine[] = {
        // positions
         1.0f,  1.0f, 0.0f,// top right
         -1.0f, -1.0f, 0.0f// bottom right
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    unsigned int bgVBO, bgVAO, bgEBO;
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glGenBuffers(1, &bgEBO);

    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBG), verticesBG, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBG), indicesBG, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    unsigned int lineVBO, lineVAO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLine), verticesLine, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    Player player{};
    Player player2{0.5f, 0.5f, 0.2f, 0.2f};
    Pistol newAmmo{7, player.getPosition('x'), player.getPosition('y'), player.getCurrentDirection(), 10};
    FireSword newAmmo1{player.getPosition('x'), player.getPosition('y'), player.getCurrentDirection(), 5};
    MathLine lineTest{player.getPosition('x'), player.getPosition('y'), player.getCurrentDirection(), 5};
    MathLine lineTest1{player.getPosition('x'), player.getPosition('y'), player.getCurrentDirection(), 5};

    lineTest.functionParser("y=2x+0.8");
    lineTest.setPosition('x', lineTest.getCenter('x'));
    lineTest.setPosition('y', lineTest.getCenter('y'));

    std::vector<Weapon> vec{};
    std::vector<Pistol> pistol{};
    std::vector<FireSword> fire_sword_vec{};
    std::vector<Player> players{};
    players.push_back(player);
    players.push_back(player2);
    pistol.push_back(newAmmo);
    fire_sword_vec.push_back(newAmmo1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("../src/container.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // Second texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width1, height1, nrChannels1;
    // load image, create texture and generate mipmaps
    data = stbi_load("../src/background.jpg", &width1, &height1, &nrChannels1, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);

    bgShader.use();
    // or set it via the texture class
    glUniform1i(glGetUniformLocation(bgShader.ID, "background"), 0);

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, players, ourShader, deltaTime, vec, pistol);
        
        // render
        // ------ rgba value/255 = answer in floats
        glClearColor(0.4f, 0.611f, 0.572f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);
        


        bgShader.use();
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(bgVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        line.use();
        lineTest.updateWindowLine(line, lineTest);
        // lineTest.move(deltaTime);
        glBindVertexArray(lineVAO);
        glDrawArrays(GL_LINES, 0, 2);

        line.use();
        lineTest1.updateWindow(line);
        // lineTest.move(deltaTime);
        glBindVertexArray(lineVAO);
        glDrawArrays(GL_LINES, 0, 2);

        // bind different Texture
        glBindTexture(GL_TEXTURE_2D, texture1);

        // render the triangle
        for (auto& obj: players) {
            ourShader.use();
            ourShader.setFloat("visible", Globals::visible);
            if (!collisionAABB(players[0], players[1])) {
                obj.gravity(deltaTime);
            }

            obj.updateScreen(ourShader);
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        for (auto& obj : vec) {
            if (obj.getPosition('x') > Map::borderX_RIGHT || obj.getPosition('x') < Map::borderX_LEFT) {
                auto it = std::find_if(vec.begin(), vec.end(), [&](const Weapon& w) {
                    return w.getId() == obj.getId();
                });
                vec.erase(it);
            }
            if (collisionAABB(players[1], obj)) {
                auto it = std::find_if(vec.begin(), vec.end(), [&](const Weapon& w) {
                    return w.getId() == obj.getId();
                });
                vec.erase(it);
                if (players[0].getCurrentWeapon() == Values::Type::pistol) {
                    player.attack(players[1], pistol[0].getDamage());
                }
                if (players[0].getCurrentWeapon() == Values::Type::fireSword) {
                    player.attack(players[1], fire_sword_vec[0].getDamage());
                }
            }

            obj.updateWindow(ourShader);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            obj.move(deltaTime);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, std::vector<Player>& vecPlayers, Shader& shader, GLfloat deltaTime, std::vector<Weapon>& vec, std::vector<Pistol>& pistol)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (!collisionAABB(vecPlayers[0], vecPlayers[1])) {
            vecPlayers[0].setPosition('r', deltaTime);
            vecPlayers[0].move(vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), shader);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!collisionAABB(vecPlayers[0], vecPlayers[1])) {
            vecPlayers[0].setPosition('l', deltaTime);
            vecPlayers[0].move(vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), shader);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!collisionAABB(vecPlayers[0], vecPlayers[1])) {
            vecPlayers[0].setPosition('d', deltaTime);
            vecPlayers[0].move(vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), shader);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!collisionAABB(vecPlayers[0], vecPlayers[1])) {
            if (vecPlayers[0].getPosition('y') == Map::ground || vecPlayers[0].getOnGround() == true) {
                vecPlayers[0].setPosition('u', deltaTime);
                vecPlayers[0].move(vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), shader);
                vecPlayers[0].setOnGround(false);
            }
        }
    }
    static bool leftWasPressed = false;
    bool leftPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (leftPressed && !leftWasPressed) {



        if (vecPlayers[0].getCurrentWeapon() == Values::Type::pistol) {
            if (pistol.at(0).getAmmo() != 0) {
                Weapon newAmmo{ vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), vecPlayers[0].getCurrentDirection(), 1, Values::Type::pistol};
                vec.push_back(newAmmo);
                ++Values::weapon_id;
                pistol[0].setAmmo(pistol[0].getAmmo() - 1);
                std::cout << "Ammo: " << pistol[0].getAmmo() << '\n';
            }
        }
        if (vecPlayers[0].getCurrentWeapon() == Values::Type::fireSword) {
            Weapon newAmmo{ vecPlayers[0].getPosition('x'), vecPlayers[0].getPosition('y'), vecPlayers[0].getCurrentDirection(), 1, Values::Type::fireSword};
            vec.push_back(newAmmo);
            ++Values::weapon_id;
        }
    }
    leftWasPressed = leftPressed;

    // Switching to the pistol
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        vecPlayers[0].setCurrentWeapon( Values::Type::pistol );
    }

    // Switching to the FireSword
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        vecPlayers[0].setCurrentWeapon( Values::Type::fireSword );
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        pistol[0].setAmmo(7);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        vecPlayers[0].setPosition('u', deltaTime);
    }
}

