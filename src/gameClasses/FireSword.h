#pragma once
#include <Weapon.h>

class FireSword : public Weapon {
private:
    float m_distance { 2.0f };

public: 
    FireSword() = default;
    int getDistance() const { return m_distance; } 

};