#include "MathLine.h"
#include <string>
#include <assert.h>
#include <cmath>

MathLine::MathLine(Values::Position point1, Values::Position point2, 
    const float x, const float y, 
    const Values::Direction direction, int damage)
    : m_point1(point1), m_point2(point2), 
    Weapon(x, y, direction, damage, Values::mathLine) {}

MathLine::MathLine(const float x, const float y, 
    const Values::Direction direction, int damage)
    : Weapon(x, y, direction, damage, Values::mathLine) {}


float MathLine::getCenter(char c) {
    switch (c)
    {
    case 'x':
        return m_centreX;
    case 'y':
        return m_centreY;
    default:
        std::cout << "MathLine::getCentre, ERROR, returned 0.0f" << std::endl;
        return 0.0f;
    }
}

float MathLine::calculateAngle() {
    float angle = std::atan((m_testK-1) / (1+1*m_testK));
    return angle;
}

// Simple function line parser ex. y = -12x + 23 or y = 12x - 0.8
void MathLine::functionParser(std::string_view func) {
    std::string left {};
    std::string right {};
    std::string func1 { func }; 
    float delim{ 10.0f };
    assert(func1.size() > 3);

    bool equal{false};
    for (size_t i = 0; i < func1.size(); ++i) {
        if (func1[i] == '=') {
            equal = true;
            continue;   
        }     
        if (!equal)
            left.push_back(func1[i]);
        else
            right.push_back(func1[i]);
    }

    bool foundPlus{ false };
    bool foundMinus{ false };
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
                if(foundMinus) {
                    beforeX.push_back(right[i]);
                }
                if (right[i] == '+') {
                    foundPlus = true;
                }
                if (right[i] == '-') {
                    foundMinus = true;
                }
            }
        } else {
            beforeXbool = true; 
            beforeX.push_back(right[i]);
            m_testK += std::stof(beforeX);
            std::cout << "k of the function is: " << m_testK << std::endl;
            m_point1.positionY += std::stof(beforeX) * 1;
            m_point2.positionY += std::stof(beforeX) * (-1);
            beforeX.clear();
        }
    }

    if (foundPlus) {
        if (std::stof(beforeX) < 1.0f ) {
            m_point1.positionY += std::stof(beforeX);
            m_point2.positionY += std::stof(beforeX);
        } else {
            m_point1.positionY += std::stof(beforeX)/delim;
            m_point2.positionY += std::stof(beforeX)/delim;
        }
    } else if (foundMinus) {
        if (std::stof(beforeX) < 1.0f ) {
            m_point1.positionY -= std::stof(beforeX);
            m_point2.positionY -= std::stof(beforeX);
        } else {
            m_point1.positionY -= std::stof(beforeX)/delim;
            m_point2.positionY -= std::stof(beforeX)/delim;
        }
    }

    // Centre
    m_centreX = (m_point1.positionX + m_point2.positionX) / 2.0f;
    m_centreY = (m_point1.positionY + m_point2.positionY) / 2.0f;

    // Length
    float dx = m_point2.positionX - m_point1.positionX;
    float dy = m_point2.positionY - m_point1.positionY;
    m_length = std::sqrt(dx*dx + dy*dy);

    std::cout << m_point1.positionX << ":" << m_point1.positionY << '\n';
    std::cout << m_point2.positionX << ":" << m_point2.positionY << '\n';
    std::cout << "Value centreX: " << m_centreX << " ---- " << "Value centreY: " << m_centreY << '\n';
    std::cout << "Length: " << m_length << '\n';
}