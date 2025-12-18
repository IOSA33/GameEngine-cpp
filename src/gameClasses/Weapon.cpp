#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "../shader.h"
#include "Weapon.h"
#include "Player.h"

void Weapon::updateWindow(const Shader& shader) const {
    auto transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(m_positionX, m_positionY, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.4f));
    
    const unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Weapon::move(const GLfloat deltaTime) {
    if (m_type == Values::Type::pistol) {
        if (m_direction == Values::Direction::RIGHT) {
            m_positionX += 0.1f * m_speed * deltaTime;
        } else {
            m_positionX -= 0.1f * m_speed * deltaTime;
        }
    }

    if (m_type == Values::Type::mathLine) {
        if (m_direction == Values::Direction::RIGHT) {
            m_positionX += 0.001f * m_speed * deltaTime;
        } else {
            m_positionX -= 0.1f * m_speed * deltaTime;
        }
    }

    if (m_type == Values::Type::fireSword) {
        if (m_direction == Values::Direction::RIGHT) {
            m_positionX = m_positionX;
        } else {
            m_positionX = m_positionX;
        }
    }
}

float Weapon::getPosition(char c) const {
    switch (c)
    {
    case 'x':
        return m_positionX;
    case 'y':
        return m_positionY;
    default:
        return 0.0f;
    }
}

bool collisionAABB(const Player& o1, const Weapon& o2) {
    const float minX_a = o1.getPosition('x') - 0.1f;
    const float maxX_a = o1.getPosition('x') + 0.1f;
    const float minX_b = o2.getPosition('x') - 0.1f;
    const float maxX_b = o2.getPosition('x') + 0.1f;

    const float minY_a = o1.getPosition('y') - 0.1f;
    const float maxY_a = o1.getPosition('y') + 0.1f;
    const float minY_b = o2.getPosition('y') - 0.1f;
    const float maxY_b = o2.getPosition('y') + 0.1f;

    const bool collisionX = minX_a <= maxX_b && maxX_a >= minX_b;
    const bool collisionY = minY_a <= maxY_b && maxY_a >= minY_b;

    // If state is true it means we have collision
    return collisionX && collisionY;
}