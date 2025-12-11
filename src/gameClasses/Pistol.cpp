#include "Pistol.h"
#include "Weapon.h"

Pistol::Pistol(int ammo, const float x, const float y, const Values::Direction direction, int damage)
     : m_ammo(ammo),
       Weapon{ x, y, direction, damage, Values::Type::pistol } {}