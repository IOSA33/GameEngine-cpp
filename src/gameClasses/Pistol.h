#pragma once
#include "Weapon.h"

class Pistol : public Weapon {
private:
    int m_ammo {};

public: 
    Pistol(int ammo, const float x, const float y, const Values::Direction direction, int damage);

    int getAmmo() const { return m_ammo; } 
    void setAmmo(int ammo) {
        m_ammo = ammo;
    }
};