#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameField.h"
#include "Wanderer.h"
#include "BeastManager.h"
#include "BuildingManager.h"
#include "CombatManager.h"
#include "InputHandler.h"
#include <memory>

class GameController {
private:
    int turnCount;
    bool gameRunning;
    bool wandererCanMove;
    bool wandererOnSlowCell;

    GameField field;
    Wanderer wanderer;
    Position wandererPosition;

    std::unique_ptr<BeastManager> beastManager;
    std::unique_ptr<BuildingManager> buildingManager;
    std::unique_ptr<CombatManager> combatManager;
    std::unique_ptr<InputHandler> inputHandler;
    
    void spawnWanderer();
    void spawnInitialBeasts();
    void renderGame() const;

public:
    GameController(int width = 15, int height = 15);
    void runGame();
};

#endif