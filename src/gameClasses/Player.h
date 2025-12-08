#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int m_hp{};
    float m_positionX{ 0.0f };
    float m_positionY{ 0.0f };

public:
    Player() = default;
    void move(float x, float y, Shader& ourShader);
    void setPosition(char c); 
    float getPosition(char c) const;
    void updateScreen(Shader& shader) const;
};

#endif