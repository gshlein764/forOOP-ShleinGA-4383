#include "GameController.h"
#include "SpellFactory.h"
#include <iostream>
#include <random>

GameController::GameController(int width, int height)
    : turnCount(0), gameRunning(true), wandererCanMove(true), wandererOnSlowCell(false), 
      field(width, height), wanderer(), wandererPosition() {
    
    spawnWanderer();

    beastManager = std::make_unique<BeastManager>(field, wandererPosition, wanderer);
    buildingManager = std::make_unique<BuildingManager>(field, *beastManager);
    combatManager = std::make_unique<CombatManager>(wanderer, *beastManager, field, wandererPosition);
    inputHandler = std::make_unique<InputHandler>(wanderer, field, wandererPosition, *combatManager, *beastManager, wandererCanMove, wandererOnSlowCell, gameRunning);
    
    spawnInitialBeasts();
    buildingManager->spawnBuildings();
    buildingManager->spawnTowers();
    SpellFactory factory;
    
    auto spell = factory.createRandomSpell();
    if (spell) {
        wanderer.learnSpell(std::move(spell));
    }
}

void GameController::spawnWanderer() {
    int x, y;
    if (field.findEmptyPosition(x, y)) {
        wandererPosition = Position(x, y);
        field.getCell(x, y).setHasWanderer(true);
    }
}
        
void GameController::spawnInitialBeasts() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 2);

    int beastCount = dis(gen);
    for (int i = 0; i < beastCount; ++i) {
        int x, y;
        if (field.findEmptyPosition(x,y)) {
            Beast beast(30, 10);
            beastManager->addBeast(Position(x, y), Beast(30, 10));
        }
    }
}

void GameController::renderGame() const {
    std::cout << "\nTurn: " << turnCount << " | Health: " << wanderer.getHealth() 
              << " | Shield: " << wanderer.getShield() << "/" << wanderer.getMaxShield()
              << " | Mana: " << wanderer.getMana() << "/" << wanderer.getMaxMana()
              << " | Score: " << wanderer.getPoints()
              << " | Mode: " << (wanderer.getCombatMode() == CombatMode::MELEE ? "MELEE" : "RANGED") << "\n";
    
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x = 0; x < field.getWidth(); ++x) {
            const Cell& cell = field.getCell(x, y);
            char symbol = '.';
            
            if (cell.getHasWanderer()) symbol = 'W';
            else if (cell.getHasBeast()) symbol = 'B';
            else if (cell.getHasBuilding()) {
                bool isTower = false;
                for (const auto& tower : buildingManager->getTowers()) {
                    if (tower.first.x == x && tower.first.y == y) {
                        symbol = 'X';
                        isTower = true;
                        break;
                    }
                }
                if (!isTower) {
                    symbol = 'T';
                }
            }
            else if (cell.getType() == CellType::OBSTACLE) symbol = '#';
            else if (cell.getType() == CellType::SLOW) symbol = '~';
            else if (cell.getHasTrap()) symbol = '^';
            
            std::cout << symbol << ' ';
        }
        std::cout << '\n';
    }
    
    std::cout << "Symbols: W-you, B-beast, T-building, X-tower, ^-trap, #-wall, ~-slow\n";
    if (wanderer.getCombatMode() == CombatMode::MELEE) {
        std::cout << "MELEE: Move into beasts to attack (adjacent cells)\n";
    } else {
        std::cout << "RANGED: Move cursor 2-3 cells away to ranged attack\n";
    }
    std::cout << "Controls: WASD-move/attack, 1-3-spells, M-show spells, C-switch mode, B - buy random spell, I-show status, Q-quit\n";
}

void GameController::runGame() {
    std::cout << "=== Game Started ===\n";
    
    while (gameRunning && wanderer.getIsAlive()) {
        turnCount++;
        renderGame();
        
        wanderer.getHand().resetSpells();

        std::cout << "Enter command: ";
        char input;
        std::cin >> input;

        if (!gameRunning || !wanderer.getIsAlive()) {
            break;
        }

        if (input == 'i' || input == 'I') {
            wanderer.displayStatus();
            turnCount--;
            continue;
        }
        
        if (input == 'm' || input == 'M') {
            wanderer.getHand().displayHand();
            std::cout << "Mana: " << wanderer.getMana() << "/" << wanderer.getMaxMana() << "\n";
            turnCount--;
            continue;
        }

        inputHandler->processInput(input);
        
        if (!wanderer.getIsAlive()) {
            std::cout << "Game Over! You died.\n";
            break;
        }
        
        if (!gameRunning) {
            break;
        }
        
        if (wanderer.getIsAlive() && turnCount % 3 == 0) {
            int oldShield = wanderer.getShield();
            wanderer.regenerateShield();
            wanderer.regenerateMana();

            if (wanderer.getShield() > oldShield) {
                std::cout << "Shield regenerated to " << wanderer.getShield() << "/" << wanderer.getMaxShield() << "!\n";
            }
        }


        if (wanderer.getIsAlive()) {
            beastManager->moveBeasts();
            buildingManager->updateBuildings();
            buildingManager->updateTowers(wandererPosition, wanderer);
            combatManager->checkCombat();
        }
    }
    
    std::cout << "Final Score: " << wanderer.getPoints() << "\n";
}