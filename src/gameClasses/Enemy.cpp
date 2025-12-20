#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(bool attack, const float x, const float y,  const float height, const float width) 
    : m_attack(attack), Player(x, y, height, width) {}


void Enemy::findPathToPlayer() {
    
}
