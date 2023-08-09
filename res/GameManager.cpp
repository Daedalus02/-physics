//
// Created by kriptos on 05/07/2023.
//

#include <stdexcept>
#include <random>
#include <chrono>
#include "../def/GameManager.h"

// CONSTRUCTORS:
GameManager::GameManager(int mode) {
    if(mode == 0){
        left_player_ = std::make_unique<players::HumanPlayer>();
        right_player_ = std::make_unique<players::HumanPlayer>();
    } else if(mode == 1){
        // Generating random number for the position of the players.
        // (Left or right side of the paddle).
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count() + 
            (std::mt19937::result_type) 
                    std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count()
        );
        std::mt19937 gen(seed);
        std::uniform_int_distribution<unsigned> distrib(0,1);
        if(distrib(gen)){
            left_player_ = std::make_unique<players::HumanPlayer>();
            right_player_ = std::make_unique<players::RobotPlayer>();
        }else{
            right_player_ = std::make_unique<players::HumanPlayer>();
            left_player_ = std::make_unique<players::RobotPlayer>();
        }
    } else if(mode == 2){
        left_player_ = std::make_unique<players::RobotPlayer>();
        right_player_ = std::make_unique<players::RobotPlayer>();
    } else{
        throw std::invalid_argument("The game mode value is invalid (possible values are 0,1,2).");
    }
    mode_ = mode;
    event_manager_ = new EventManager();
}

// MEMBER FUNCTIONS/OPERATORS:
GameManager &GameManager::getInstance(int mode) {
    static GameManager gameManager(mode);
    return gameManager;
}



