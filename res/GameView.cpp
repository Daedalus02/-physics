//
// Created by kriptos on 04/07/2023.
//

#include "../def/GameView.h"
#include "../def/GameModel.h"

View& View::getInstance(){
    static View view;
    return view;
}
View::View(){
    Model::GetInstance().Attach(this);
}

void View::update(const std::string &message) {
    message_ = message;
}

View::~View(){

}
