//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_GRAPHICSTOOLS_H
#define PONG_GRAPHICSTOOLS_H

/*
 *
 * */
#include <iostream>
#include "GameObject.h"

namespace graphics_tools {

    constexpr float kSmall = 0.001;
    /*
     * Base implementation of coordinates in the paddle_, other classes inheriting from this are accepted
     * */
    class Coordinate {
    public:
        // CONSTRUCTORS:
        // This constructor sets the internal variable of the coordinates with the given ones (default value is 0).
        Coordinate(float x = 0, float y = 0) : x_(x), y_(y) {};

        // MEMBER FUNCTIONS/OPERATORS
        // This function returns the value of the x coordinate.
        float getX() const {
            return x_;
        }

        // This function returns the value of the y coordinate.
        float getY() const {
            return y_;
        }

        // This function sets the value of the x coordinate.
        void setX(float x) {
            x_ = x;
        }

        // This function sets the value of the y coordinate.
        void setY(float y) {
            y_ = y;
        }

        // Compound assignment for sum operator.
        Coordinate& operator+=(const Coordinate& coord);

        // Compound assignment for minus operator.
        Coordinate& operator-=(const Coordinate& coord);

        // Equality operator.
        bool operator==(const Coordinate &coord) const;

        // Inequality operator.
        bool operator!=(const Coordinate &coord) const;

        // DESTRUCTOR:
        ~Coordinate(){}

    private:
        // MEMBER ATTRIBUTES:
        // This variable represents the x-axis coordinate.
        float x_ = 0;
        // This variable represents the y-axis coordinate.
        float y_ = 0;
    };

    //HELPER FUNCTIONS/OPERATORS:
    // Sum operator.
    Coordinate operator+(const Coordinate &coord1, const Coordinate &coord2);

    // Minus operator.
    Coordinate operator-(const Coordinate &coord1, const Coordinate &coord2);

    // Insertion operator.
    std::ostream& operator<<(std::ostream& os, const Coordinate& coord);

    // This function return the angle between the two point in the given coordinate.
    float getCoordinatesAngle(const Coordinate& coord1, const Coordinate coord2);

    // This function returns true if the given coordinates are equals in the integer sets.
    bool bigger(const Coordinate& coord1, const Coordinate& coord2, const Coordinate& direction);

    // This function returns true if the two float are approximately the same.
    bool proxFloat(float number1, float number2);

    // This function returns the distance between the given coordinates.
    float getDistance(const Coordinate& coordinate1, const Coordinate& coordinate2);
    /**
     */
    class GraphicObject : public GameObject{
    public:
        // CONSTRUCTOR:
        GraphicObject(float angle, float velocity,char symbol, float weight, float height, const graphics_tools::Coordinate& center);

        // MEMBER FUNCTIONS/OPERATORS:
        // Setters and getters for private variables.
        const Coordinate &getCenter() const{
            return center_;
        }
        void setCenter(const Coordinate &center) {
            GraphicObject::center_ = center;
        }
        float getAngle() const {
            return angle_;
        }
        void setAngle(float angle) {
            GraphicObject::angle_ = angle;
        }
        char getSymbol(){return symbol_;}
        // This function returns true if the given coordinate is inside the graphic object.
        bool contains(const Coordinate& coordinate) const;
        // This function returns true if the object is a valid one(has a dimension).
        bool isValid() const;
        // Equality operator.
        bool operator==(const GraphicObject& graphicObject) const;
        // Inequality operator.
        bool operator!=(const GraphicObject& graphicObject) const;

        // DESTRUCTOR:
        ~GraphicObject(){}
    private:
        // This variable is the center of the graphic object.
        graphics_tools::Coordinate center_;
        // This variable is the angle of the graphic object movement.
        float angle_;
        // This variable is the symbol for the representation of this graphic object.
        char symbol_;
    };

    // HELPER FUNCTIONS/OPERATORS:
    // This function returns the upper edge object of another existing object.
    GraphicObject getUpperEdge(const GraphicObject& graphicObject);
    // This function returns the down edge object of another existing object.
    GraphicObject getDownEdge(const GraphicObject& graphicObject);
    // This function returns the left edge object of another existing object.
    GraphicObject getLeftEdge(const GraphicObject& graphicObject);
    // This function returns the right edge object of another existing object.
    GraphicObject getRightEdge(const GraphicObject& graphicObject);
}


#endif //PONG_GRAPHICSTOOLS_H
