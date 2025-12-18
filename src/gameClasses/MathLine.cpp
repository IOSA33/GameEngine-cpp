#include "MathLine.h"
#include <string>
#include <assert.h>

MathLine::MathLine(Values::Position point1, Values::Position point2, 
    const float x, const float y, 
    const Values::Direction direction, int damage)
    : m_point1(point1), m_point2(point2), 
    Weapon(x, y, direction, damage, Values::mathLine) {}

MathLine::MathLine(const float x, const float y, 
    const Values::Direction direction, int damage)
    : Weapon(x, y, direction, damage, Values::mathLine) {}


// Simple function line parser ex. y = 12x + 23
void MathLine::functionParser(std::string_view func) {
    std::string left {};
    std::string right {};

    float delim{ 10.0f };
    assert(func.size() > 3);

    bool equal{false};
    for (size_t i = 0; i < func.size(); ++i) {
        if (!equal)
            left.push_back(func[i]);
        else
            right.push_back(func[i]);
        if (func[i] == '=')
            equal = true;    
    }

    bool foundPlus{ false };
    bool beforeXbool{ false };
    std::string beforeX{};
    for (size_t i = 0; i < right.size(); ++i) {
        if (right[i+1] != 'x') {
            if (!beforeXbool)
                beforeX.push_back(right[i]);
            if (beforeXbool) {
                if(foundPlus) {
                    beforeX.push_back(right[i]);
                }
                if (right[i] == '+') {
                    foundPlus = true;
                }
            }
        } else {
            beforeXbool = true;
            beforeX.push_back(right[i]);
            m_point1.positionY += std::stof(beforeX) * 1;
            m_point2.positionY += std::stof(beforeX) * (-1);
            beforeX.clear();
        }
    }

    m_point1.positionY += std::stof(beforeX)/delim;
    m_point2.positionY += std::stof(beforeX)/delim;

    std::cout << m_point1.positionX << ":" << m_point1.positionY << '\n';
    std::cout << m_point2.positionX << ":" << m_point2.positionY << '\n';
}