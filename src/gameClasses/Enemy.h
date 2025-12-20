#pragma once

#include "Player.h"

class Enemy : public Player {
    bool m_attack{ false };

public:
    Enemy(bool attack, const float x, const float y,  const float height, const float width);

    void findPathToPlayer();    
};