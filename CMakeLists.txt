cmake_minimum_required(VERSION 3.24)
project(Pong)

set(CMAKE_CXX_STANDARD 17)
add_executable(Pong src/main.cpp res/Ball.cpp res/GameView.cpp def/Wall.h def/Paddle.h res/Paddle.cpp res/GameModel.cpp res/GraphicsTools.cpp res/GameObject.cpp res/MoveController.cpp)
