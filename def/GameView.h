//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_GAMEVIEW_H
#define PONG_GAMEVIEW_H

#include <iostream>
#include "ObserverTools.h"
#include "GameModel.h"

class View : public Observer{
public:
    //PUBLIC CONSTRICTORS:
    // Deleted copy constructor.
    View(const View& view) = delete;

    // MEMBER FUNCTIONS/OPERATORS:
    // This function updates the viewed state of the Model class instance.
    void update(const std::string& message) override;
    // This function returns the unique instance of this class used in this system.
    static View& getInstance();
    // Deleted copy assignment.
    View& operator=(const View& view) = delete;

    // DESTRUCTOR:
    // This is an empty destructor since this class does not hold any kind of resources.
    ~View();
private:
    // PRIVATE CONSTRUCTORS:
    // This constructor sets the Model considered in this class unique instance.
    View();

    // MEMBER ATTRIBUTES:
    // This string hold the current viewed state of the observed Model class instance.
    std::string message_;
};


#endif //PONG_GAMEVIEW_H
