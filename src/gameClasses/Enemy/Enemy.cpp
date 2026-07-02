#include <vector>
#include <iostream>
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"
#include "../Weapon/Weapon.h"

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