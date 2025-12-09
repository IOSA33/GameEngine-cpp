#include "../shader.h"
#pragma once

class Player;
namespace Values;

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
    Weapon(float x, float y, Values::Direction direction) 
        : m_positionX(x), m_positionY(y), m_direction(direction) {}
        
    void updateWindow(Shader& shader) const;
    void move(GLfloat deltaTime);
    float getPosition(char c) const;
    int getDamage() { return m_damage; };
    
    friend bool collisionAABB(Player& o1, Weapon& o2);
};

#endif