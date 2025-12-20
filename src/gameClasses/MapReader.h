#pragma once

#include <iostream>
#include <array>
#include <string>
#include <vector>

class Shader;

class MapReader{
    int m_level{};
    std::string m_path{};
    std::vector<std::vector<int>> m_levelVec = std::vector<std::vector<int>>(11, std::vector<int>(11));
    std::vector<float> m_positionsToRender{};
public:
    MapReader(int level, std::string_view path) : m_level(level), m_path(path) {}
    void readLevelFile();
    std::vector<float> getLevelVec() const { return m_positionsToRender; }
    void loadMap(Shader& shader, const unsigned int& vao);
    void MapUpdate(const float x, const float y, Shader& shader);
};