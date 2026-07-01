cmake_minimum_required(VERSION 3.10)
project(opengl_project)

set(CMAKE_CXX_STANDARD 23)

# Step 1 Ubuntu

# - GLFW -
# sudo apt-get install libglfw3
# sudo apt-get install libglfw3-dev

# - OpenGL -
# sudo apt-get install libgl-dev

# - Ninja-build - 
# sudo apt install ninja-build

# Step 2 

# mkdir build
# cd build
# cmake .. -G Ninja
# ninja
# if everything's OKAY, then ./app.exe, it should create an app Window

# GLAD
add_library(glad ${PROJECT_SOURCE_DIR}/Libraries/include/glad/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/include)

# main.exe
add_executable(app main.cpp
                   src/gameClasses/Player.cpp
                   src/gameClasses/Weapon.cpp
                   src/gameClasses/Pistol.cpp
                   src/gameClasses/FireSword.cpp
                   src/gameClasses/MathLine.cpp
                   src/gameClasses/MapReader.cpp
                   src/gameClasses/Enemy.cpp
                   
                   #src/Network/server.cpp
                   #src/Network/client.cpp
                   )

# GLFW
find_package(glfw3 3.4 REQUIRED)

# OpenGl
find_package(OpenGL REQUIRED)

# linking everything together
target_link_libraries(app
        glad
        glfw
        OpenGL::GL
)
