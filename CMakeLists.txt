cmake_minimum_required(VERSION 3.10)
project(opengl_project)

set(CMAKE_CXX_STANDARD 17)

# pacman -S mingw-w64-x86_64-cmake. For cmake on Windows
# pacman -S mingw-w64-x86_64-glfw. For including glfw in minGW64
# when executing it will take every .h files from minGW/lib.. etc

# For starting:
# mkdir build, then cd build
# cmake ..
# ninja
# if everything's OKAY, then ./app.exe, it should create a Window

# GLAD
add_library(glad ${PROJECT_SOURCE_DIR}/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/include)

# main.exe
add_executable(app main.cpp
                   src/gameClasses/Player.cpp
                   src/gameClasses/Weapon.cpp
                   src/gameClasses/Pistol.cpp
                   src/gameClasses/FireSword.cpp
                   src/gameClasses/MathLine.cpp
                   src/gameClasses/MapReader.cpp
                   src/Network/server.cpp
                   src/Network/client.cpp)

# GLFW from MSYS2/MinGW64
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# linking everything together
target_link_libraries(app
        glad
        ${GLFW_LIBRARIES}
        opengl32
        ws2_32
)
