#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Player.h"
#include <glad/glad.h>
#include "../shader.h"

void Player::move(float x, float y, Shader& ourShader) {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));

    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

float Player::getPosition(char c) const {
    switch (c)
    {
    case 'x':
        return m_positionX;
        break;
    case 'y':
        return m_positionY;
    default:
        return 0.0f;
    }
}

void Player::setPosition(char c) {
	const std::string op = "player/setPosition()";
	switch (c)
	{
	case 'r':
        if (!(getPosition('x') > 1.0f)) {
            m_positionX += 0.02f;
        }
		break;
	case 'l':
        if (!(getPosition('x') < -1.0f)) {
            m_positionX -= 0.02f;
        }
		break;
    case 'u':
		if (!(getPosition('y') > 1.0f)) {
            m_positionY += 0.02f;
        }
		break;
	case 'd':
		if (!(getPosition('y') < -1.0f)) {
            m_positionY -= 0.02f;
        }
		break;
	default:
		std::cout << op << ": default break\n";
        // zigissä se olis viel helpompaa
		break;
	}
}

void Player::updateScreen(Shader& shader) const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(m_positionX, m_positionY, 0.0f));

    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}