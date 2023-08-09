//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_WALL_H
#define PONG_WALL_H
#include "GameObject.h"

class Wall : public GameObject{
public:
    // CONSTRUCTORS:
    // This constructor sets dimension and velocity of this object in the playground.
    Wall(float velocity, float weight, float height) : GameObject(velocity, weight, height) {}

    // DESTRUCTOR:
    ~Wall(){};
};


#endif //PONG_WALL_H
