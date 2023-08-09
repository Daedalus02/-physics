//
// Created by kriptos on 04/07/2023.
//
#include <iostream>
#ifndef PONG_OBSERVERTOOLS_H
#define PONG_OBSERVERTOOLS_H

class Observer {
public:
    virtual ~Observer(){};
    virtual void update(const std::string& message) = 0;
};

class Subject {
public:
    virtual ~Subject(){};
    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
    virtual void Notify() = 0;
};


#endif //PONG_OBSERVERTOOLS_H
