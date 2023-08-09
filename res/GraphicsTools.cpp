//
// Created by kriptos on 25/07/2023.
//

#include "../def/GraphicsTools.h"
#include <cmath>

// HELPER FUNCTIONS:
graphics_tools::Coordinate graphics_tools::operator+(const graphics_tools::Coordinate& coord1, const graphics_tools::Coordinate& coord2) {
    return (graphics_tools::Coordinate(coord1.getX() + coord2.getX(), coord1.getY() + coord2.getY()));
}
graphics_tools::Coordinate graphics_tools::operator-(const graphics_tools::Coordinate &coord1, const graphics_tools::Coordinate &coord2){
    return (graphics_tools::Coordinate(coord1.getX() - coord2.getX(), coord1.getY() - coord2.getY()));
}
bool graphics_tools::Coordinate::operator==(const Coordinate &coord) const{
    if(x_ == coord.x_ && y_ == coord.y_){
        return true;
    }
    return false;
}
bool graphics_tools::Coordinate::operator!=(const Coordinate &coord) const{
    if(x_ != coord.x_ || y_ != coord.y_){
        return true;
    }
    return false;
}
std::ostream& graphics_tools::operator<<(std::ostream& os, const graphics_tools::Coordinate& coord){
    os << "X: ";
    os << coord.getX();
    os << " y: ";
    os << coord.getY();
    return os;
    }
bool graphics_tools::GraphicObject::operator==(const GraphicObject &graphicObject) const {
   if(center_ == graphicObject.center_ && angle_ == graphicObject.angle_ &&
        getHeight() == graphicObject.getHeight() && getWeight() == graphicObject.getWeight() &&
        getVelocity() == graphicObject.getVelocity()){
        return true;
    }
    return false;
}
bool graphics_tools::GraphicObject::operator!=(const GraphicObject &graphicObject) const {
    if(center_ != graphicObject.center_ || angle_ != graphicObject.angle_ ||
       getHeight() != graphicObject.getHeight() || getWeight() != graphicObject.getHeight() ||
       getVelocity() != graphicObject.getVelocity()){
        return true;
    }
    return false;
}
bool graphics_tools::bigger(const graphics_tools::Coordinate& coord1, const graphics_tools::Coordinate& coord2,
                            const graphics_tools::Coordinate& direction ){
    if((proxFloat(0,direction.getX()) || (coord1.getX()-coord2.getX())/direction.getX() > 0) &&
        (proxFloat(0,direction.getY()) || (coord1.getY()-coord2.getY())/direction.getY() > 0)){
        return true;
    }
    return false;
}
graphics_tools::GraphicObject graphics_tools::getUpperEdge(const graphics_tools::GraphicObject& graphicObject){
    graphics_tools::GraphicObject edge(0,0,graphicObject.getWeight(),1,
                                       graphicObject.getCenter() + graphics_tools::Coordinate(0,+graphicObject.getHeight()/2));
    return edge;
}
graphics_tools::GraphicObject graphics_tools::getDownEdge(const graphics_tools::GraphicObject& graphicObject){
    graphics_tools::GraphicObject edge(0,0,graphicObject.getWeight(),1,
                                       graphicObject.getCenter() + graphics_tools::Coordinate(0,-graphicObject.getHeight()/2));
    return edge;
}
graphics_tools::GraphicObject graphics_tools::getLeftEdge(const graphics_tools::GraphicObject& graphicObject){
    graphics_tools::GraphicObject edge(0,0,graphicObject.getWeight(),1,
                                       graphicObject.getCenter() + graphics_tools::Coordinate(-graphicObject.getWeight()/2,0));
    return edge;
}
graphics_tools::GraphicObject graphics_tools::getRightEdge(const graphics_tools::GraphicObject& graphicObject){
    graphics_tools::GraphicObject edge(0,0,graphicObject.getWeight(),1,
                                       graphicObject.getCenter() + graphics_tools::Coordinate(+graphicObject.getWeight()/2,0));
    return edge;
}


// COORDINATE:
// MEMBER FUNCTIONS/OPERATORS:
graphics_tools::Coordinate& graphics_tools::Coordinate::operator+=(const graphics_tools::Coordinate& coord){
    this->x_ += + coord.getX();
    this->y_ += + coord.getY();
    return *this;
}
graphics_tools::Coordinate& graphics_tools::Coordinate::operator-=(const graphics_tools::Coordinate& coord){
    this->x_ -= coord.getX();
    this->y_ -= coord.getY();
    return *this;
}

// GRAPHIC OBJECT
graphics_tools::GraphicObject::GraphicObject (float angle, float velocity, char symbol, float weight, float height,
                                                 const graphics_tools::Coordinate& center) : GameObject(velocity, weight, height)
    : angle_{angle}, center_ {center}, symbol_{symbol}{}

bool graphics_tools::GraphicObject::contains(const Coordinate &coordinate) const {
    float weight_add = 0;
    float height_add = 0;
    if(std::abs(center_.getX() - coordinate.getX()) == getWeight()/2){
        weight_add = kSmall;
    }
    if(std::abs(center_.getY() - coordinate.getY()) == getHeight()/2){
        height_add = kSmall;
    }
    if(((center_.getX() + (getWeight()/2 + weight_add)) >= coordinate.getX()) && ((center_.getX() - (getWeight()/2 - weight_add)) <= coordinate.getX()) &&
            ((center_.getY() + (getHeight()/2 + height_add)) >= coordinate.getY()) && ((center_.getY() - (getHeight()/2 - height_add)) <= coordinate.getY())){
        return true;
    }
    return false;
}
bool graphics_tools::GraphicObject::isValid() const {
    if(getHeight() == 0 || getWeight() == 0) {
        return false;
    }
    return true;
}

float graphics_tools::getCoordinatesAngle(const graphics_tools::Coordinate& coord1, const graphics_tools::Coordinate coord2) {
    float atan_angle = atan2((coord2.getY()-coord1.getY()),(coord2.getX()-coord1.getX())) * (180/M_PI);
    return atan_angle;
}

bool graphics_tools::proxFloat(float number1, float number2){
    if(std::abs(number1-number2) < kSmall){
        return true;
    }
    return false;
}
float graphics_tools::getDistance(const graphics_tools::Coordinate& coordinate1, const graphics_tools::Coordinate& coordinate2){
    return sqrt(pow(coordinate2.getY() - coordinate1.getY(),2) + pow(coordinate2.getX() - coordinate1.getX(),2));
}