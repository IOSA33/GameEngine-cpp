#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int hp{};

public:
    void move(float offsetX, float offsetY, Shader& ourShader);
};

#endif