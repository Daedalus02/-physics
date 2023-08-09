//
// Created by kriptos on 06/07/2023.
//

#include "../def/MoveController.h"
#include <cmath>

MoveController &MoveController::GetInstance(int delay, int proportion, const EventManagerPtr& managerPtr) {
    static MoveController controller(delay, proportion, managerPtr);
    return controller;
}

MoveController::MoveController(int delay, int proportion, const EventManagerPtr& managerPtr) : paddle_{std::make_unique<Paddle>(proportion)},
                                                            delay_{delay}, eventManagerPtr{managerPtr}{}

void MoveController::Move(const graphics_tools::GraphicObject& graphicObject, int frames) {
    // Checking if the time frame is too big.
    if(frames * delay_ > kMaxTimeLapse){
        throw std::invalid_argument("The value of time lapse entered for this move is too big!");
    }

    // Calculating total interval and total distance.
    float interval = frames*delay_;
    float distance = interval*graphicObject.getVelocity();

    // Getting the value of the paddle weight and height.
    float paddle_weight = paddle_->getXDimension() - 1;
    float paddle_height = paddle_->getYDimension() - 1;

    // Setting the final position of the moving element in the paddle.
    while(distance > 0){
        float angle = -graphicObject.getAngle();
        //std::cout<<"The current value of the angle is: "<<angle<<std::endl;
        graphics_tools::Coordinate center = graphicObject.getCenter();
        //std::cout<<"The current value of the center is: "<<center<<std::endl;
        float cos_angle = cos(angle*(M_PI/180));
        float sin_angle = sin(angle*(M_PI/180));
        //std::cout<<"The value of the cos is: "<<cos_angle<<std::endl;
        //std::cout<<"The value of the sin is: "<<sin_angle<<std::endl;
        graphics_tools::Coordinate current_delta(0,0);
        // Calculating current delta and total delta.
        if (cos_angle > 0) {
            current_delta.setX(paddle_weight - center.getX());
        } else {
            current_delta.setX(center.getX());
        }
        if (sin_angle > 0) {
            current_delta.setY(paddle_height - center.getY());
        } else {
            current_delta.setY(center.getY());
        }
        // Calculating the number of shifts necessary to get to an edge or to the final position.
        float n_shifts = std::min(std::abs(current_delta.getY() / sin_angle), std::abs(current_delta.getX() / cos_angle));
        current_delta.setX(n_shifts * cos_angle);
        current_delta.setY(n_shifts * sin_angle);
        //std::cout<<"The current value of the delta is: "<<current_delta<<std::endl;
        // Calculating the current destination for a movement inside the paddle.
        graphics_tools::Coordinate destination = graphicObject.getCenter() + current_delta;
        float current_distance = graphics_tools::getDistance(graphicObject.getCenter(),destination);
        //std::cout<<"The current value of the distance is: "<<current_distance<<std::endl;
        if(current_distance > distance){
            float fraction = distance / current_distance;
            current_distance = distance;
            current_delta.setX(current_delta.getX()*fraction);
            current_delta.setY(current_delta.getY()*fraction);
            destination = graphicObject.getCenter() + current_delta;
        }
        // Securing the positivity of the destination coordinates.
        destination.setY(std::abs(destination.getY()));
        destination.setX(std::abs(destination.getX()));
        //std::cout<<"The current destination coordinate is: "<<destination<<std::endl;
        // Moving the object in the paddle.
        paddle_->Move(center,destination);
        distance -= current_distance;
    }
    //std::cout<<"The final value of distance variable is: "<<distance<<std::endl;
}

