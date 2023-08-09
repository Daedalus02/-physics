//
// Created by kriptos on 04/07/2023.
//

#include "../def/GameController.h"

//CONSTRUCTOR:
Controller::Controller() {
    Model::GetInstance().Attach(this);
}

// MEMBER FUNCTIONS/OPERATORS:
Controller &Controller::getInstance() {
    static Controller controller;
    return controller;
}
void Controller::update(const std::string &message) {
    message_ = message;
}

// DESTRUCTOR:
Controller::~Controller() noexcept {

}