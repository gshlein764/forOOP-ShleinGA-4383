#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "GameField.h"
#include "Wanderer.h"
#include "BeastManager.h"
#include "SpellFactory.h"

class CombatManager {
private:
    Wanderer& wanderer;
    BeastManager& beastManager;
    GameField& field;
    Position wandererPosition;
    int killCounter;

public:
    CombatManager(Wanderer& wanderer, BeastManager& beastManager, GameField& field, const Position& wandererPos);
    
    void processMeleeAttack(const Position& targetPos);
    void processRangedAttack(int directionX, int directionY);
    void checkCombat();
    void updateWandererPosition(const Position& newPos) {
        wandererPosition = newPos;
    }
private:
    void checkSpellRewards(int killedBeasts);
};

#endif