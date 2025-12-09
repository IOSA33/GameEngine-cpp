#pragma once
#include <Weapon.h>

class Pistol : public Weapon {
private:
    int m_ammo { 20 };

public: 
    Pistol(int ammo) : m_ammo(ammo) {}
    int getAmmo() const { return m_ammo; } 
    
};