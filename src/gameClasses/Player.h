#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"

#ifndef PLAYER_H
#define PLAYER_H

namespace Values {
    constexpr float gravity { -9.81f };
    constexpr float jumpStrenght{ 5.0f };
};

class Player {
private:
    int m_hp{};
    float m_positionX{ 0.0f };
    float m_positionY{ 0.0f };
    float m_PlayerSpeed{ 15.0f };
    float m_velocity { 0.0f };

public:
    Player() = default;
    Player(float x, float y) 
        : m_positionX(x), m_positionY(y) {};

    void move(float x, float y, Shader& ourShader);
    void setPosition(char c, GLfloat deltaTime); 
    void setPositionHard(char c, float a);
    float getPosition(char c) const;
    void updateScreen(Shader& shader) const;
    void gravity(GLfloat deltaTime);
    friend bool collisionAABB(const Player& o1, const Player& o2);
    
};

#endif