#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include "../shader.h"

class Weapon;

namespace Values {
    constexpr float gravity { -9.81f };
    constexpr float jumpStrenght{ 4.0f };

    enum Direction {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    enum Type {
        pistol,
        fireSword,
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
    Values::Type m_currentWeapon{};
    Weapon* m_weapon{};

public:
    Player() = default;
    Player(const float x, const float y,  const float height, const float width)
        : m_positionX(x), m_positionY(y), m_height(height), m_width(width) {};

    void move(float x, float y, const Shader& ourShader);
    void setPosition(char c, GLfloat deltaTime); 
    void setPositionHard(char c, float a);
    [[nodiscard]] float getPosition(char c) const;
    void updateScreen(const Shader& shader) const;
    void gravity(GLfloat deltaTime);
    void setVelocity(const float x) { m_velocity = x; }
    void attack(Player& player, int damage);
    void setHp(const int x) { m_hp = x; }
    [[nodiscard]] int getHp() const { return m_hp; }
    [[nodiscard]] bool getOnGround() const { return m_onGround; }
    void setOnGround(const bool x) {m_onGround = x; }
    [[nodiscard]] float getHeight() const { return m_height; }
    [[nodiscard]] float getWidth() const { return m_width; }
    [[nodiscard]] Values::Direction getCurrentDirection() const { return m_direction; }
    void setDirection(Values::Direction x);
    Values::Type getCurrentWeapon() const { return m_currentWeapon; }
    void setCurrentWeapon(Values::Type weaponType) { m_currentWeapon = weaponType; }

    static Values::Direction getDirection(char c);
    friend bool collisionAABB(Player& o1, const Player& o2);
};

#endif