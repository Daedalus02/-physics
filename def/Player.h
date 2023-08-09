//
// Created by kriptos on 04/07/2023.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

namespace players{
class Player {
public:
    // PUBLICS CONSTRUCTORS: 
    Player();
    // MEMBER FUNCTIONS/OPERATORS:
    // This function allow the player to play a move.
    bool virtual Move();
    // DESTRUCTOR:
    ~Player();
private:

};
}
#endif //PONG_PLAYER_H
