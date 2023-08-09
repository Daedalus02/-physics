//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_GAMECONTROLLER_H
#define PONG_GAMECONTROLLER_H

#include "GameModel.h"
/*
 * This class is the component used in this system to allow its state and operations to interact (being updated/used)
 * with the user by using a notify/push protocol.
 * */

class Controller : public Observer {
public:
    // PUBLIC CONSTRUCTOR:
    // Deleted copy constructor.
    Controller(const Controller& controller) = delete;

    // MEMBER FUNCTIONS/OPERATORS:
    // This function return the single instance of this class used in the system.
    static Controller& getInstance();
    // This function updates the viewed state of the Model class instance.
    void update(const std::string& message) override;
    // Deleted copy assignment.
    Controller& operator=(const Controller& controller) = delete;

    // DESTRUCTOR:
    ~Controller();

private:
    // PRIVATE CONSTRUCTORS:
    // This constructor sets the model of the controller.
    Controller();

    // MEMBER ATTRIBUTES:
    // This string hold the current viewed state of the observed Model class instance.
    std::string message_;
};


#endif //PONG_GAMECONTROLLER_H
