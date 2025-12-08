#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Player.h"
#include <glad/glad.h>
#include "../shader.h"
#include <algorithm>

namespace Map {
    float borderX_RIGHT { 1.0f };
    float borderX_LEFT { -1.0f };
    float borderY_UP { 1.0f };
    float borderY_DOWN { -1.0f };
    float ground { -0.5f };
}

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

void Player::setPosition(char c, GLfloat deltaTime) {
	const std::string op = "player/setPosition()";
	switch (c)
	{
	case 'r':
        if (!(getPosition('x') > 1.0f)) {
            m_positionX += 0.1f * m_PlayerSpeed * deltaTime;
        }
		break;
	case 'l':
        if (!(getPosition('x') < -1.0f)) {
            m_positionX -= 0.1f * m_PlayerSpeed * deltaTime;
        }
		break;
    case 'u':
		if (!(getPosition('y') > 1.0f)) {
            m_velocity = Values::jumpStrenght;
            m_velocity -= Values::gravity * deltaTime;
            m_positionY += m_velocity * deltaTime;
        }
		break;
	case 'd':
		if (!(getPosition('y') < -1.0f)) {
            m_positionY -= 0.1f * m_PlayerSpeed * deltaTime;
        }
		break;
	default:
		std::cout << op << ": default break\n";
		break;
	}
}

void Player::updateScreen(Shader& shader) const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(m_positionX, m_positionY, 0.0f));

    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Player::gravity(GLfloat deltaTime) {
    m_velocity += Values::gravity * deltaTime;
    m_positionY += m_velocity * deltaTime;
    if (getPosition('y') < -0.5f) {
        m_positionY = -0.5f;
        m_velocity = 0.0f;
    }
}

void Player::setPositionHard(char c, float a) {
    switch (c)
    {
    case 'x':
        m_positionX = a;
        break;
    case 'y':
        m_positionY = a;
        break;
    
    default:
        break;
    }
}

bool collisionAABB(Player& o1, Player& o2) {
    float minX_a = o1.getPosition('x') - 0.1f;
    float maxX_a = o1.getPosition('x') + 0.1f;
    float minX_b = o2.getPosition('x') - 0.1f;
    float maxX_b = o2.getPosition('x') + 0.1f;

    float minY_a = o1.getPosition('y') - 0.1f;
    float maxY_a = o1.getPosition('y') + 0.1f;
    float minY_b = o2.getPosition('y') - 0.1f;
    float maxY_b = o2.getPosition('y') + 0.1f;

    bool collisionX = minX_a <= maxX_b && maxX_a >= minX_b;
    bool collisionY = minY_a <= maxY_b && maxY_a >= minY_b;

    // If state is true it means we have collision
    bool state = collisionX && collisionY;
    if (state) {
        float overlapX = std::min(maxX_a, maxX_b) - std::max(minX_a, minX_b);
        float overlapY = std::min(maxY_a, maxY_b) - std::max(minY_a, minY_b);

        if (overlapX < overlapY) {
            if (maxX_a > maxX_b)
                o1.setPositionHard('x', o1.getPosition('x') + overlapX);
            else
                o1.setPositionHard('x', o1.getPosition('x') - overlapX);
        } else {
            o1.setVelocity(0.0f);
            if (maxY_a > maxY_b)
                o1.setPositionHard('y', o1.getPosition('y') + overlapY);
            else
                o1.setPositionHard('y', o1.getPosition('y') - overlapY);
                o1.m_onGround = true;
        }
    }

    return false;
}

void Player::attack(Player& player, int damage) {
    if (player.m_hp > 0) {
        player.setHp(player.getHp() - damage);
        std::cout << "Enemy has hp left: " << player.getHp() << '\n';
    } 
}
