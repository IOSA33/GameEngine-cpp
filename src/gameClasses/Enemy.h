#pragma once

#include "Player.h"

class Weapon;

class Enemy : public Player {
    bool m_attack{ false };

public:
    Enemy(bool attack, const float x, const float y,
         const float height, const float width, float playerSpeed);

    void findPathToPlayer(const std::vector<Player>& playerVec, float deltaTime);

    friend bool collisionAABB(const Enemy& o1, const Weapon& o2);
};