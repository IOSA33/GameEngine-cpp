#include "MapReader.h"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Player.h"
#include <glad/glad.h>
#include "../shader.h"

void MapReader::readLevelFile() {
    std::ifstream file(m_path);
    if (!file.is_open()) {
        std::cout << "MapReader::readLevelFile(): Cannot open a file!" << std::endl;
        return;
    }

    float startPosX{ -1.0f };
    float startPosY{  1.0f };
    
    std::string text{};
    int i{ 0 };
    while(std::getline(file, text)) {
        
        for (size_t j = 0; j < text.size(); ++j) {
            if (text[j] - '0' == 1) {
                m_positionsToRender.emplace_back(startPosX);
                m_positionsToRender.emplace_back(startPosY);
            }
            m_levelVec[i][j] = text[j] - '0';
            startPosX += 0.2f;
        }
        startPosX = -1.0f;
        startPosY -= 0.2f;
        ++i;
    }


    for(size_t i = 0; i < m_levelVec.size(); ++i) {
        for(size_t j = 0; j < m_levelVec.size(); ++j) {
            std::cout << m_levelVec[i][j];
        }
        std::cout << std::endl;
    }
}

void MapReader::MapUpdate(const float x, const float y, Shader& shader) {
    auto transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));

    const unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void MapReader::loadMap(Shader& shader, const unsigned int& VAO) {
    for (size_t i = 0; i < m_positionsToRender.size(); i += 2) {
        shader.use();
        MapUpdate(m_positionsToRender[i], m_positionsToRender[i + 1], shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}