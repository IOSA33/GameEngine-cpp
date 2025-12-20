#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"

Enemy::Enemy(bool attack, const float x, const float y, 
    const float height, const float width, float playerSpeed) 
    : m_attack(attack), Player(x, y, height, width, playerSpeed) {}

void Enemy::findPathToPlayer(const std::vector<Player>& playerVec, float deltaTime) {
    if (playerVec[0].getPosition('x') - getPosition('x') > 0.09f) {
        setPosition('r', deltaTime);
    } else if (playerVec[0].getPosition('x') - getPosition('x') < -0.09f) {
        setPosition('l', deltaTime);
    }
}

bool collisionAABB(const Enemy& o1, const Weapon& o2) {
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