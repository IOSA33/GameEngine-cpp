# GameEngine-cpp with OpenGL

Game Engine based on OpenGl that runs 2d FPS game with two player with multiplayer

In this project:
- NetWork Connection via WinSock2
- 2D world
- You can draw any kind of mathematical function lines in chat input in real time 

# How to Start Ubuntu version

## Step 1
### GLFW
```
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```

### OpenGL
```
sudo apt-get install libgl-dev
```

### Ninja-build 
```
sudo apt install ninja-build
```

## Step 2 

```
mkdir build
cd build
cmake .. -G Ninja
ninja
./app.exe
```