#pragma once
#include "Weapon.h"

class FireSword : public Weapon {
private:
    float m_distance { 0.3f };

public: 
    FireSword() = default;
    FireSword(const float x, const float y, const Values::Direction direction, int damage);
    int getDistance() const { return m_distance; } 

};