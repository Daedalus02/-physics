//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_GAMEMODEL_H
#define PONG_GAMEMODEL_H

#include <iostream>
#include <list>
#include "../def/ObserverTools.h"

/*
 *
 * */

class Model : public Subject{
public:
    // PUBLIC CONSTRUCTORS:
    // Deleted copy constructor.
    Model(const Model& model) = delete;

    // MEMBER FUNCTIONS/OPERATORS:
    // This function allow observers to be notified with the state of this class instances.
    void Attach(Observer* observer) override;
    // This function remove the given observer if present, if not present it fails silently.
    void Detach(Observer* observer) override;
    // This function notify all the attached observer
    void Notify() override;
    // This function set the message to use when notifying the attached observer.
    void SetMessage(const std::string& message);
    // This function returns the only instance of this class used in the system.
    static Model& GetInstance();
    // Deleted copy assignment.
    Model& operator=(const Model& model) = delete;

    // DESTRUCTOR:
    ~Model();

private:
    // PRIVATE CONSTRUCTORS:
    // No-argument constructor (no state needed to be set at the beginning).
    Model(){};

    // MEMBER ATTRIBUTES:
    // This list is used to store the observer attached to this subject in a given moment.
    std::list<Observer*> observers_;
    // This string is the set message to return to observer when notifying.
    std::string message_;
};


#endif //PONG_GAMEMODEL_H
