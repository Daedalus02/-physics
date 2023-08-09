//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_BAR_H
#define PONG_BAR_H

#include "GameObject.h"

class Bar : public GameObject {
public:
    // CONSTRUCTORS:
    // This constructor sets dimension and velocity of this object in the playground.
    Bar(float velocity, float weight, float height) : GameObject(velocity, weight, height) {}

    // DESTUCTOR:
    ~Bar(){};
};


#endif //PONG_BAR_H
