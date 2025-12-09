#pragma once
#include "../shader.h"
#include "Player.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon {
    enum Type {
        pistol,
        fireball,
    };

private:
    Type type{ pistol };
    int m_damage{ 1 };
    float m_positionX{};
    float m_positionY{};
    Values::Direction m_direction{ Values::Direction::RIGHT };
    float m_speed{ 20.0f };

public:
    Weapon() = default;
    Weapon(const float x, const float y, const Values::Direction direction)
        : m_positionX(x), m_positionY(y), m_direction(direction) {}
        
    void updateWindow(const Shader& shader) const;
    void move(GLfloat deltaTime);
    [[nodiscard]] float getPosition(char c) const;
    [[nodiscard]] int getDamage() const { return m_damage; };
    
    friend bool collisionAABB(const Player& o1, const Weapon& o2);
};

#endif