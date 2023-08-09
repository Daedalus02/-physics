//
// Created by kriptos on 05/07/2023.
//

#ifndef PONG_GAMEMANAGER_H
#define PONG_GAMEMANAGER_H

#include "Player.h"
#include "HumanPlayer.h"
#include "RobotPlayer.h"
#include "EventManager.h"
#include <memory>
#include <queue>

/**
 * Three different modalities are supported by this class depending on the value 
 * of the member attribute mode_:
 * - mode_ = 0 --> the game is played by two human players.
 * - mode_ = 1 --> the game is played by one human player and a bot.
 * - mode_ = 2 --> the game is played by two bots.
 */
class GameManager {
public:
    // PUBLIC CONSTRUCTOR:
    // Deleted copy constructor:
    GameManager(const GameManager& gameManager) = delete;

    // MEMBER FUNCTIONS/OPERATORS:
    // This function returns the single instance of this class used in the system.
    static GameManager& getInstance(int mode = 0);
    // Deleted copy assignment.
    GameManager& operator=(const GameManager& gameManager) = delete;
    // This function return the modality of the current game.
    int getMode() {return mode_;} 
    // This function returns a const reference to the left player.
    const players::Player& getLeftPlayer() const {return *left_player_;}
    // This function returns a const reference to the right player.
    const players::Player& getRightPlayer() const {return *right_player_;}

private:
    // PRIVATE CONSTRUCTOR:
    // This constructor instantiates the unique instance of this class used in the system.
    GameManager(int mode);

    // MEMBER ATTRIBUTES:
    // This variable is an integer representing the modality of the current game.
    int mode_;
    // This variable represent the left player.
    std::unique_ptr<players::Player> left_player_;
    // This variable represent the right player.
    std::unique_ptr<players::Player> right_player_;
    // This variable is a queue of event that the system need to manage.
    std::queue<int> event_queue_;
    // This variable store the event manager shared pointer of the system.
    EventManagerPtr  event_manager_;
};


#endif //PONG_GAMEMANAGER_H
