#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "../def/GameModel.h"
#include "../def/GameView.h"
#include "../def/GameController.h"
#include "../def/Paddle.h"
#include "../def/MoveController.h"


int main() {
    /*Paddle paddle = Paddle(1);
    std::cout<<paddle;
    paddle.Move(paddle.getBall().getCenter(),graphics_tools::Coordinate(20,0));
    std::cout<<paddle;
    std::cout<<paddle.getBall().getCenter()<<std::endl;
    paddle.Move(paddle.getBall().getCenter(),graphics_tools::Coordinate(17,17));
    std::cout<<paddle;
    std::cout<<paddle.getBall().getCenter()<<std::endl;*/
    MoveController& controller = MoveController::GetInstance(10,1);
    Paddle& paddle = controller.getPaddle();
    paddle.setAngle(paddle.getBall(),199);
    system("[console]::CursorVisible = $false");
    //controller.Move(paddle.getBall(), 1);
    //std::cout<<paddle.getBall().getCenter();
    while(true) {
        controller.Move(paddle.getBall(), 1);
        system("cls");
        std::cout<<paddle;
        Sleep(100);
    }
    return 0;
}
