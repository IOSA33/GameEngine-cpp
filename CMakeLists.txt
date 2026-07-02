cmake_minimum_required(VERSION 3.10)
project(opengl_project)

set(CMAKE_CXX_STANDARD 23)

# GLAD
add_library(glad ${PROJECT_SOURCE_DIR}/Libraries/include/glad/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/include)

# ./app.exe
add_executable(app main.cpp
                   src/gameClasses/Player/Player.cpp
                   src/gameClasses/Weapon/Weapon.cpp
                   src/gameClasses/Pistol/Pistol.cpp
                   src/gameClasses/FireSword/FireSword.cpp
                   src/gameClasses/MathLine/MathLine.cpp
                   src/gameClasses/MapReader/MapReader.cpp
                   src/gameClasses/Enemy/Enemy.cpp
                   
                   #src/Network/server.cpp
                   #src/Network/client.cpp
                   )

# GLFW
find_package(glfw3 3.4 REQUIRED)

# OpenGl
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

# linking everything together
target_link_libraries(app
        glad
        glfw
        OpenGL::GL
)
