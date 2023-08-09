//
// Created by kriptos on 04/07/2023.
//

#include <iostream>
#include <list>
#include "../def/GameModel.h"

//MEMBER FUNCTIONS/OPERATORS:
void Model::Attach(Observer *observer) {
    observers_.push_back(observer);
}
void Model::Detach(Observer *observer) {
    observers_.remove(observer);
}
void Model::Notify() {
    std::list<Observer*>::iterator iter = observers_.begin();
    while(iter != observers_.end()){
        (*iter)->update(message_);
        ++iter;
    }
}
void Model::SetMessage(const std::string &message) {
        message_ = message;
}
Model& Model::GetInstance(){
      static Model model;
      return model;
}

// DESTRUCTORS:
Model::~Model(){
    SetMessage("");
    Notify();
    std::list<Observer*>::iterator iter = observers_.begin();
    while(iter != observers_.end()){
        Detach(*iter);
        ++iter;
    }
}