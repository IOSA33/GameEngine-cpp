#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "../shader.h"
#include "Weapon.h"
#include "Player.h"

void Weapon::updateWindow(Shader& shader) const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(m_positionX, m_positionY, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.3f));
    
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Weapon::move(GLfloat deltaTime) {
    m_positionX += 0.1f * m_speed * deltaTime;
}

float Weapon::getPosition(char c) const {
    switch (c)
    {
    case 'x':
        return m_positionX;
        break;
    case 'y':
        return m_positionY;
        break;
    default:
        return 0.0f;
        break;
    }
}

bool collisionAABB(Player& o1, Weapon& o2) {
    float minX_a = o1.getPosition('x') - 0.2f;
    float maxX_a = o1.getPosition('x') + 0.2f;
    float minX_b = o2.getPosition('x') - 0.2f;
    float maxX_b = o2.getPosition('x') + 0.2f;

    float minY_a = o1.getPosition('y') - 0.2f;
    float maxY_a = o1.getPosition('y') + 0.2f;
    float minY_b = o2.getPosition('y') - 0.2f;
    float maxY_b = o2.getPosition('y') + 0.2f;

    bool collisionX = minX_a <= maxX_b && maxX_a >= minX_b;
    bool collisionY = minY_a <= maxY_b && maxY_a >= minY_b;

    // If state is true it means we have collision
    return collisionX && collisionY;
}