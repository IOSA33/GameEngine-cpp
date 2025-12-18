#include "Weapon.h"
#include "Player.h"
#include <string>

class MathLine : public Weapon {
    Values::Position m_point1{};
    Values::Position m_point2{};

public:
    MathLine() = default;
    MathLine(Values::Position point1, Values::Position point2, const float x, const float y, const Values::Direction direction, int damage);
    explicit MathLine(const float x, const float y, const Values::Direction direction, int damage);

    void functionParser(std::string_view func);
};