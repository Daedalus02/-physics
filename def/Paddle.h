//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include <iostream>
#include <memory>
#include <list>
#include "GraphicsTools.h"
#include "Bar.h"
#include "Ball.h"
#include "Wall.h"

// Defining the standard values of objects graphical properties.
constexpr unsigned int kDefaultWeight = 40;
constexpr unsigned int kDefaultHeight = 25;

constexpr float kBallHeight = 1;
constexpr float kBallWeight = 1;
constexpr float kBallVelocity = 0.5;
constexpr float kWallHeight = 1;
constexpr float kWallWeight = 40;
constexpr float kWallVelocity = 0;
constexpr float kBarHeight = 20;
constexpr float kBarWeight = 1;
constexpr float kBarVelocity = 2;
constexpr char kDefaultSymbol = '#';
constexpr char kDefaultEmpty = ' ';
constexpr char kBarSymbol = '|';
constexpr char kBallSymbol = 'o';
constexpr char kWallSymbol = '#';


/*
 * DEFINITION: This class represents the element containing all the other objects in the game.
 *      -It operates indirectly on the object of the game through their graphical wrapper
 *      to be able to have an indication of their velocity, angle and position in each
 *      time frame.
 *
 * */
class Paddle {
public:
    // PUBLIC CONSTRUCTORS:
    // No-argument constructor.
    Paddle(unsigned int proportion = 1);

    // PUBLIC MEMBER FUNCTIONS/OPERATORS:
    // Getters and setters for member attributes and their properties.
    const graphics_tools::GraphicObject& getUpperWall() const {return upper_wall_;};
    const graphics_tools::GraphicObject& getDownWall() const {return down_wall_;};
    const graphics_tools::GraphicObject& getBar1() const {return bar1_;};
    const graphics_tools::GraphicObject& getBar2() const {return bar2_;};
    const graphics_tools::GraphicObject& getBall() const {return ball_;};
    void setCenter(const graphics_tools::GraphicObject& graphicObject, const graphics_tools::Coordinate& center);
    void setAngle(const graphics_tools::GraphicObject& graphicObject, float angle);
    void setVelocity(const graphics_tools::GraphicObject& graphicObject, float velocity);
    float getXDimension() const {return x_dimension_;}
    float getYDimension() const {return y_dimension_;}
    char getBarSymbol
    // This function returns true if the given graphical object new position is valid.
    bool isValid(const graphics_tools::GraphicObject& graphicObject, const graphics_tools::Coordinate& center);
    // This function return the element in the given coordinate (if not present return null dimension element).
    const graphics_tools::GraphicObject& getElement(const graphics_tools::Coordinate& position) const;
    // This function return the list of object crossed in a given trajectory.
    // (trajectory deduced from the two given coordinates)
    std::list<graphics_tools::GraphicObject> getCrossed(graphics_tools::Coordinate& begin, graphics_tools::Coordinate& end);

    // This function move a component inside the paddle_ (return true if the move was possible else false).
    bool Move(const graphics_tools::Coordinate& center, const graphics_tools::Coordinate& destination);

    // DESTRUCTOR:
    ~Paddle(){}

private:
    //PRIVATE MEMBER FUNCTIONS/OPERATORS:
    // This function return the element in the given coordinate (if not present return null dimension element).
    graphics_tools::GraphicObject& getElement(const graphics_tools::Coordinate& position);

    // MEMBER ATTRIBUTES:
    // This variable is the ball contained in the paddle.
    graphics_tools::GraphicObject ball_;
    // This variable is the first player Bar.
    graphics_tools::GraphicObject bar1_;
    // This variable is the second player Bar.
    graphics_tools::GraphicObject bar2_;
    // This variable is the upper element of the wall.
    graphics_tools::GraphicObject upper_wall_;
    // This variable is the down element of the wall.
    graphics_tools::GraphicObject down_wall_;
    // This variable is the empty space.
    graphics_tools::GraphicObject empty_space;
    // This variable is the x dimension of the paddle.
    float x_dimension_;
    // This variable is the y dimension of the paddle.
    float y_dimension_;
};

// HELPER FUNCTION/OPERATORS:
// This is the insertion operator.
std::ostream& operator<<(std::ostream& os,const Paddle& paddle);

#endif //PONG_PADDLE_H
