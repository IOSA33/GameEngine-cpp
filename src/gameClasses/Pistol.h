#pragma once
#include <Weapon.h>

class Pistol : public Weapon {
private:
    int m_ammo { 20 };

public: 
    Pistol(int ammo, const float x, const float y, const Values::Direction direction, int damage)
     : m_ammo(ammo),
       Weapon{ x, y, direction, damage } {}

    int getAmmo() const { return m_ammo; } 
    void setAmmo(int ammo) { ammo = m_ammo; }
};