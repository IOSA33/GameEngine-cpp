#include "FireSword.h"
#include "Weapon.h"

FireSword::FireSword(const float x, const float y, const Values::Direction direction, int damage)
     : Weapon{ x, y, direction, damage, Values::Type::fireSword } {}