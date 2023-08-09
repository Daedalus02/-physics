//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_GAMEOBJECT_H
#define PONG_GAMEOBJECT_H




class GameObject{
public:
    // CONSTRUCTORS:
    // This constructor sets the velocity of the component in the playground.
    GameObject(float velocity = 0, float weight = 0, float height = 1);

    // MEMBER FUNCTION/OPERATORS:
    // Velocity getter.
    float getVelocity() const { return velocity_;}
    // weight getter.
    float getWeight() const { return weight_;}
    // Height getter.
    float getHeight() const { return height_;}
    // Velocity setter.
    void setVelocity(float velocity) {velocity_ = velocity;}
private:
    // MEMBER ATTRIBUTES:
    // This variable contains the velocity of the GameObject class (cannot be change after being set first).
    float velocity_;
    // This variable contains the height of the GameObject class (cannot be change after being set first).
    float height_;
    // This variable contains the weight of the GameObject class (cannot be change after being set first).
    float weight_;
};


#endif //PONG_GAMEOBJECT_H
