#pragma once

#include "Weapon.h"
#include "Player.h"
#include <string>

class MathLine : public Weapon {
    Values::Position m_point1{.positionX = 1.0f, .positionY = 0.0f};
    Values::Position m_point2{.positionX = -1.0f, .positionY = 0.0f};
    float m_centreX{};
    float m_centreY{};
    float m_testK{ 0.0f };
    float m_length{ 0.0f };

public:
    MathLine() = default;
    MathLine(Values::Position point1, Values::Position point2, const float x, const float y, const Values::Direction direction, int damage);
    explicit MathLine(const float x, const float y, const Values::Direction direction, int damage);

    float calculateAngle();
    void functionParser(std::string_view func);
    float getCenter(char c);
    float getLength() const {return m_length; }
};