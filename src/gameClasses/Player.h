#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"

namespace Values {
    constexpr float gravity { -9.81f };
    constexpr float jumpStrenght{ 4.0f };

    enum Direction {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };
}

namespace Map {
    extern float borderX_RIGHT;
    extern float borderX_LEFT;
    extern float borderY_UP;
    extern float borderY_DOWN;
    extern float ground;
}

class Player {
private:
    int m_hp{ 100 };
    float m_positionX{ 0.0f };
    float m_positionY{ 0.0f };
    float m_PlayerSpeed{ 15.0f };
    float m_velocity { 0.0f };
    bool m_onGround { false };
    float m_height{};
    float m_width{};
    Values::Direction m_direction{ Values::Direction::RIGHT };

public:
    Player() = default;
    Player(float x, float y, float height, float width) 
        : m_positionX(x), m_positionY(y), m_height(height), m_width(width) {};

    void move(float x, float y, Shader& ourShader);
    void setPosition(char c, GLfloat deltaTime); 
    void setPositionHard(char c, float a);
    float getPosition(char c) const;
    void updateScreen(Shader& shader) const;
    void gravity(GLfloat deltaTime);
    void setVelocity(const float x) { m_velocity = x; };
    void attack(Player& player, int damage);
    void setHp(int x) { m_hp = x; };
    int getHp() { return m_hp; }; 
    bool getOnGround() const { return m_onGround; };
    void setOnGround(bool x) {m_onGround = x; };
    float getHeight() { return m_height; };
    float getWidth() { return m_width; };
    Values::Direction getCurrentDirection() { return m_direction; };
    void setDirection(Values::Direction x);


    static Values::Direction getDirection(char c);
    friend bool collisionAABB(Player& o1, Player& o2);
};

#endif