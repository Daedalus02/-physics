//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <iostream>
#include "GameObject.h"

class Ball : public GameObject{
public:
    // PUBLIC CONSTRUCTORS:
    // This constructor sets dimension and velocity of this object in the playground.
    Ball(float velocity, float weight, float height) : GameObject(velocity, weight, height) {}

    // DESTRUCTOR:
    ~Ball(){};
};


#endif //PONG_BALL_H
