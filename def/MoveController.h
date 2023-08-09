//
// Created by kriptos on 06/07/2023.
//

#ifndef PONG_MOVECONTROLLER_H
#define PONG_MOVECONTROLLER_H

#include <iostream>
#include <memory>
#include <boost/function>
#include "Paddle.h"
#include "GameObject.h"
#include "EventManager.h"

/* This constant is the maximum value of the lapse for
   the Move function of the MoveController in Milliseconds.*/
constexpr float kMaxTimeLapse = 100;

class MoveController {
public:
    // PUBLIC CONSTRUCTORS
    // Deleted copy constructor.
    MoveController(const MoveController& moveController) = delete;

    // PUBLIC DEFINITIONS:
    // This is the signature of the wall hit event.
    typedef void WallHitEventFnSignature(char symbol);
    typedef boost::function<WallHitEventFnSignature> WallHitEventFn;
    // This is the signature of start moving object event.
    typedef void MovingEventFnSignature(char symbol);
    typedef boost::function<MovingEventFnSignature> MovingEventFn;
    // This is the signature of the end moving object event

    // MEMBER FUNCTION/OPERATORS:
    // This function returns the single instance of this class used by the system
    // (it take the time delay as argument).
    static MoveController& GetInstance(int delay = 50, int proportion = 1, const EventManagerPtr& managerPtr);
    // Deleted copy assignment.
    MoveController& operator=(const MoveController& moveController) = delete;
    // This function move the given GameObject (if speed is different from 0).
    void Move(const graphics_tools::GraphicObject& graphicObject, int frames);
    // This function returns the single instance of paddle used in this class.
    Paddle& getPaddle() {return *paddle_.get();}


private:
    // PRIVATE CONSTRUCTORS:
    // This constructor set the time delay of the controller (in milliseconds).
    MoveController(int delay, int proportion, const EventManagerPtr& managerPtr);

    // MEMBER ATTRIBUTES:
    // This variable is the instance of Paddle used to do the calculation in this class.
    std::unique_ptr<Paddle> paddle_;
    // This variable is the time delay(ms) used to move perpetually moving elements (e.g. the ball)
    int delay_;
    // This variable is the system event manager shared pointer.
    EventManagerPtr eventManagerPtr;
};


#endif //PONG_MOVECONTROLLER_H
