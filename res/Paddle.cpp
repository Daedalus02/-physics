//
// Created by kriptos on 04/07/2023.
//

#include "../def/Paddle.h"
#include <stdexcept>
#include <list>
#include <cmath>

Paddle::Paddle(unsigned int proportion) :
    x_dimension_(proportion*kDefaultWeight),
    y_dimension_(proportion*kDefaultHeight),
    ball_(0,kBallVelocity*proportion, kBallSymbol,kBallWeight*proportion, kBallHeight*proportion,
                                           graphics_tools::Coordinate(proportion*kDefaultWeight/2,proportion*kDefaultHeight/2)),
    bar1_(0,kBarVelocity*proportion,kBarSymbol,kBarWeight*proportion, kBarHeight*proportion,
                                           graphics_tools::Coordinate(proportion*kDefaultWeight/20,proportion*kDefaultHeight/2)),
    bar2_(0,kBarVelocity*proportion,kBarSymbol, kBarWeight*proportion, kBarHeight*proportion,
                                           graphics_tools::Coordinate((proportion*kDefaultWeight*19)/20,proportion*kDefaultHeight/2)),
    upper_wall_(0,kWallVelocity*proportion, kWallSymbol, static_cast<float> (proportion*kDefaultWeight),kWallHeight*proportion,
                                                 graphics_tools::Coordinate(proportion*kDefaultWeight/2,kWallHeight)),
    down_wall_(0, kWallVelocity*proportion, kWallSymbol,static_cast<float>(proportion*kDefaultWeight), kWallHeight*proportion,
                                                graphics_tools::Coordinate(proportion*kDefaultWeight/2,proportion*kDefaultHeight-kWallHeight*proportion)),
    empty_space(0,0,0,0,graphics_tools::Coordinate(-1,-1)){
    // Do nothing.
}

bool Paddle::Move(const graphics_tools::Coordinate& center, const graphics_tools::Coordinate& destination) {
    // Printing the coordinates passed as arguments.
    //std::cout << "The begin coordinates are: " << center << std::endl;
    //std::cout << "The end coordinates are: " << destination <<std::endl;
    //std::cout << "The dimension of the paddle are: \nx: "<<x_dimension_<<"\ny: "<<y_dimension_<<std::endl;
    // This variable's value is true if the moving object hit another one in its trajectory.
    bool crossed = false;
    // Checking the destination walls validity
    if(destination.getX() >= 0 && destination.getX() < x_dimension_
        && destination.getY() >= 0 && destination.getY() < y_dimension_) {
        // Determination and check of the moving object.
        const graphics_tools::GraphicObject& object = getElement(center);
        if(object.isValid()){
            // Getting the entrance angle between begin and end coordinates.
            float angle = -graphics_tools::getCoordinatesAngle(center,destination);
            if(angle <= 0){
                angle += 360;
            }
            if(angle > 360){
                angle -= 360;
            }
            // Printing the value of the angle between begin and end coordinates.
            //std::cout << "The angle between the beginning and end coordinates is: " << angle << std:: endl;
            // Determination of the final angle (the reflection one).
            float final_angle = angle;
            // Determining the increments of x and y dimensions for the begin-end distance.
            graphics_tools::Coordinate increment(cos(-angle*(M_PI / 180))/10,sin(-angle*(M_PI / 180))/10);
            // Printing the value of the increment coordinates:
            //std::cout << "The value of the increment for begin coordinates is: " << increment << std::endl;
            // Determination of the correct sides of the moving object to check for collisions.
            // (Depend on the entrance angle).
            graphics_tools::Coordinate begin_x;
            graphics_tools::Coordinate begin_y;
            graphics_tools::Coordinate edge;
            if(angle <= 90) {
                begin_x.setX(object.getCenter().getX() - object.getWeight() / 2);
                begin_x.setY(object.getCenter().getY() + object.getHeight() / 2);
                begin_y.setY(object.getCenter().getY() - object.getHeight() / 2);
                begin_y.setX(object.getCenter().getX() + object.getWeight() / 2);
                edge.setX(object.getCenter().getX() + object.getWeight() / 2);
                edge.setY(object.getCenter().getY() + object.getHeight() / 2);
            }else if (angle <= 180){
                begin_x.setX(object.getCenter().getX() + object.getWeight() / 2);
                begin_x.setY(object.getCenter().getY() + object.getHeight() / 2);
                begin_y.setY(object.getCenter().getY() - object.getHeight() / 2);
                begin_y.setX(object.getCenter().getX() - object.getWeight() / 2);
                edge.setX(object.getCenter().getX() - object.getWeight() / 2);
                edge.setY(object.getCenter().getY() + object.getHeight() / 2);
            }else if (angle <= 270){
                begin_x.setX(object.getCenter().getX() + object.getWeight() / 2);
                begin_x.setY(object.getCenter().getY() - object.getHeight() / 2);
                begin_y.setY(object.getCenter().getY() + object.getHeight() / 2);
                begin_y.setX(object.getCenter().getX() - object.getWeight() / 2);
                edge.setX(object.getCenter().getX() - object.getWeight() / 2);
                edge.setY(object.getCenter().getY() - object.getHeight() / 2);
            }else if (angle <= 360){
                begin_x.setX(object.getCenter().getX() - object.getWeight() / 2);
                begin_x.setY(object.getCenter().getY() - object.getHeight() / 2);
                begin_y.setY(object.getCenter().getY() + object.getHeight() / 2);
                begin_y.setX(object.getCenter().getX() + object.getWeight() / 2);
                edge.setX(object.getCenter().getX() + object.getWeight() / 2);
                edge.setY(object.getCenter().getY() - object.getHeight() / 2);
            }
            //std::cout << "The edge coordinate is: " << edge << std::endl;
            //std::cout << "The begin edge coordinate in x-axis is: " << begin_x << std::endl;
            //std::cout << "The begin edge coordinate in y-axis is: " << begin_y << std::endl;
            // This variable is used to keep track of the different position
            // frames between begin and end point of the movement.
            graphics_tools::Coordinate tmp_coord = center;
            // Setting all the edge elements to next postion.
            // This variable store the first object crossed using the determined increment
            // and evolving from begin position to the end one (default is the moving object itself).
            graphics_tools::GraphicObject first_crossed = object;
            while(!graphics_tools::bigger(tmp_coord,destination,increment)){
                graphics_tools::GraphicObject tmp_obj = getElement(edge);
                // This is a list of element crossed in the y line considered for collisions.
                std::list<graphics_tools::GraphicObject> y_crossed;
                if(angle != 90 && angle != 270) {
                    y_crossed = getCrossed(begin_y, edge);
                }
                // This is a list of element crossed in the x line considered for collisions.
                std::list<graphics_tools::GraphicObject> x_crossed;
                if(angle != 180 && angle != 360 && angle != 0) {
                    x_crossed = getCrossed(begin_x, edge);
                }
                std::list<graphics_tools::GraphicObject>::iterator iter_x = x_crossed.begin();
                std::list<graphics_tools::GraphicObject>::iterator iter_y = y_crossed.begin();
                /* Checking whether there has been or not a collision in the x line considered for
                 * collisions (begin_x to tmp_coord) iterating through the x_crossed list.
                 * */
                while(iter_x != x_crossed.end()){
                    // If a crossed object is valid and is not the moving one we found the first crossed.
                    if(iter_x->isValid() && *iter_x != object){
                        first_crossed = *iter_x;
                        // Setting the angle to the reflection one.
                        if(graphics_tools::getDownEdge(first_crossed).contains(tmp_coord) ||
                             graphics_tools::getUpperEdge(first_crossed).contains(tmp_coord)){
                            final_angle = 360 - final_angle;
                        }else{
                            final_angle = 180 - final_angle;
                        }
                        if(final_angle < 0){
                            final_angle += 360;
                        }
                        //std::cout<<"The value of the reflection angle is: "<<final_angle<<std::endl;
                        setAngle(object, final_angle);
                        crossed = true;
                        //std::cout<<"crossed at "<< tmp_coord<<std::endl;
                        break;
                    }
                    iter_x++;
                }
                /* Checking whether there has been or not a collision in the y line considered for
                 * collisions (begin_y to tmp_coord) iterating through the y_crossed list.
                 * */
                while(iter_y != y_crossed.end() && !crossed){
                    // If a crossed object is valid and is not the moving one we found the first crossed.
                    if(iter_y->isValid() && *iter_y != object){
                        first_crossed = *iter_y;
                        // Setting the angle to the reflection one.
                        if(getDownEdge(first_crossed).contains(tmp_coord)){
                            // If the moving object come from the downside of the hit object.
                            if((tmp_coord - increment).getY() > graphics_tools::getDownEdge(first_crossed).getCenter().getY()){
                                // Possible values of angle here are from 0 (excluded) to 180 (included).
                                if(angle < 90){    // Range: ]0,90[.
                                    final_angle = 360 - final_angle;
                                }else{  // Range: [90,180].
                                    final_angle = 360 - final_angle;
                                }
                            }else{
                                // Possible values of angle here are from 180 (excluded) to 360 (included).
                                if(angle < 270){    // Range: ]180,270[.
                                    final_angle = 360 - final_angle;
                                }else{    // Range: [270,360].
                                    final_angle = 360 - final_angle;
                                }
                            }
                        }else if(getUpperEdge(first_crossed).contains(tmp_coord)){
                            // If the moving object come from the upper side of the hit object.
                            if((tmp_coord - increment).getY() < graphics_tools::getDownEdge(first_crossed).getCenter().getY()){
                                // Possible values of angle here are from 180 (excluded) to 360 (included).
                                if(angle < 270){    // Range: ]180,270[.
                                    final_angle = 360 - final_angle;
                                }else{    // Range: ]270,360].
                                    final_angle = 360 - final_angle;
                                }
                            }else{
                                // Possible values of angle here are from 0 (excluded) to 180 (included).
                                if(angle < 0){    // Range: ]0,90[.
                                    final_angle = 360 - final_angle;
                                }else{    // Range: [90,180].
                                    final_angle = 360 - final_angle;
                                }
                            }
                        }else if(graphics_tools::getRightEdge(first_crossed).contains(tmp_coord)){
                            // If the moving object come from the right side of the hit object.
                            if((tmp_coord - increment).getX() > graphics_tools::getDownEdge(first_crossed).getCenter().getX()){
                                // Possible value of angle here are from 90 (excluded) to 270 (included).
                                if(angle < 180){     // Range: ]90,180[.
                                    final_angle = 180 - final_angle;
                                }else{    // Range: [180,270].
                                    final_angle = 180 - final_angle;
                                }

                            }else{
                                // Possible value of angle here are from 270 (excluded) to 360 (included) and from 0 (excluded) to 90 (included).
                                if(angle <= 90){    // Range: ]0,90].
                                    final_angle = 180 - final_angle;
                                }else{    // Range: [270,360].
                                    final_angle = 180 - final_angle;
                                }
                            }
                        }else{
                            // If the moving object come from the left side of the hit object.
                            if((tmp_coord - increment).getX() < graphics_tools::getDownEdge(first_crossed).getCenter().getX()){
                                // Possible value of angle here are from 270 (excluded) to 360 (included) and from 0 (excluded) to 90 (included).
                                if(angle <= 90){   // Range: ]0,90].
                                    final_angle = 180 - final_angle;
                                }else{   // Range: ]270,360].
                                    final_angle = 180 - final_angle;
                                }
                            }else{
                                // Possible value of angle here are from 90 (excluded) to 270 (included).
                                if(angle < 180){    // Range: ]90,180[.
                                    final_angle = 180 - final_angle;
                                }else{     // Range: [180,270].
                                    final_angle = 180 - final_angle;
                                    if(final_angle < 0){
                                        final_angle += 360;
                                    }
                                }
                            }
                        }

                        if(final_angle < 0){
                            final_angle += 360;
                        }
                        setAngle(object,final_angle);
                        //std::cout<<"The value of the reflection angle is: "<<final_angle<<std::endl;
                        crossed = true;
                        //std::cout<<"crossed at "<< tmp_coord<<std::endl;
                        break;
                    }
                    iter_y++;
                }
                // Checking if the moving object was stopped by another one in its trajectory.
                // (Exiting the moving cycle if true).
                if (crossed){
                    tmp_coord -= increment;
                    break;
                }
                //std::cout<<"The current value of the center is: "<<object.getCenter();
                // Incrementing the tracked position of the object with the movement increment.
                begin_x += increment;
                begin_y += increment;
                edge += increment;
                tmp_coord += increment;
                /*std::cout<<std::endl;
                std::cout<<"The tmp coord is "<<tmp_coord<<std::endl;
                std::cout<<"The edge coord is "<<edge<<std::endl;
                std::cout<<"The begin x coord is "<<begin_x<<std::endl;
                std::cout<<"The begin y coord is "<<begin_y<<std::endl<<std::endl;*/
            }
            if(crossed) {
                setCenter(object,tmp_coord);
            }else{
                setCenter(object,(tmp_coord-increment));
            }
        }
    }
    return !crossed;
}

graphics_tools::GraphicObject& Paddle::getElement(const graphics_tools::Coordinate& position) {
    return const_cast<graphics_tools::GraphicObject&>(const_cast<const Paddle*>(this)->getElement(position));
}

const graphics_tools::GraphicObject& Paddle::getElement(const graphics_tools::Coordinate& position) const {
    // Checking if one of the element in the paddle contains the position.
    if (ball_.contains(position)) {
        return ball_;
    } else if (bar1_.contains(position)) {
        return bar1_;
    } else if (bar2_.contains(position)) {
       return bar2_;
    } else if (upper_wall_.contains(position)){
        return upper_wall_;
    } else if (down_wall_.contains(position)){
        return down_wall_;
    }
    // If no match was found returning an invalid graphic object.
    return empty_space;
}
void Paddle::setCenter(const graphics_tools::GraphicObject& graphicObject, const graphics_tools::Coordinate& center){
    graphics_tools::GraphicObject& validObject = this->getElement(graphicObject.getCenter());
    if(validObject.isValid() && isValid(validObject,center)){
        validObject.setCenter(center);
    }
    //std::cout<<validObject.getCenter()<<std::endl;
}
void Paddle::setAngle(const graphics_tools::GraphicObject& graphicObject, float angle){
    graphics_tools::GraphicObject& validObject = this->getElement(graphicObject.getCenter());
    if(validObject.isValid()){
        validObject.setAngle(angle);
    }
}
void Paddle::setVelocity(const graphics_tools::GraphicObject& graphicObject, float velocity){
    graphics_tools::GraphicObject& validObject = this->getElement(graphicObject.getCenter());
    if(validObject.isValid() && velocity < std::min(x_dimension_, y_dimension_)){
        validObject.setVelocity(velocity);
    }
}

bool Paddle::isValid(const graphics_tools::GraphicObject& graphicObject, const graphics_tools::Coordinate& center){
    if((center.getX() - graphicObject.getWeight() / 2) > 0 && (center.getX() + graphicObject.getWeight() / 2) < x_dimension_ &&
        (center.getY() - graphicObject.getHeight() / 2) > 0 && (center.getY() + graphicObject.getHeight() / 2) < y_dimension_){
            return true;
        }
}
// HELPER FUNCTION/OPERATORS:
std::ostream& operator<<(std::ostream& os,const Paddle& paddle){
    for(int i = 0; i < paddle.getYDimension(); i++){
        for(int j = 0; j < paddle.getXDimension(); j++){
            if(paddle.getElement(graphics_tools::Coordinate(j, i)).isValid()){
                os<<kDefaultSymbol;
            } else {
                os<<kDefaultEmpty;
            }
        }
        os << '\n';
    }
    return os;
}



std::list<graphics_tools::GraphicObject> Paddle::getCrossed(graphics_tools::Coordinate& begin, graphics_tools::Coordinate& end) {
    // Initializing the list with all the object crossed in the given line.
    std::list<graphics_tools::GraphicObject> crossed_elements;
    // Initializing the evolving position in the line (from begin to end).
    graphics_tools::Coordinate tmp_coord = begin;
    // Determining the angle of the line from the positive x-axis.
    int angle = graphics_tools::getCoordinatesAngle(begin,end);
    // Determining the line position increment to progress from begin to end.
    graphics_tools::Coordinate increment(cos(angle*(M_PI / 180))/10,sin(angle*(M_PI / 180))/10);
    while(!graphics_tools::bigger(tmp_coord,end,increment)){
        /* Checking whether the current considered position in the line is
         * inside a valid object.*/
        graphics_tools::GraphicObject tmp_obj = getElement(tmp_coord);
        if(tmp_obj.isValid()){
            // Adding the valid element in the crossed list.
            crossed_elements.push_back(tmp_obj);
        }
        // Incrementing the current position.
        tmp_coord += increment;
    }
    return crossed_elements;
}
