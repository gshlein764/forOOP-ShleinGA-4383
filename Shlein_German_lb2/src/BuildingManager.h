#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include "GameField.h"
#include "BeastBuilding.h"
#include "BeastManager.h"
#include "EnemyTower.h"
#include <vector>

class BuildingManager {
private:
    std::vector<std::pair<Position, BeastBuilding>> buildings;
    std::vector<std::pair<Position, EnemyTower>> towers;
    GameField& field;
    BeastManager& beastManager;

public:
    BuildingManager(GameField& field, BeastManager& beastManager);
    
    void updateBuildings();
    void updateTowers(const Position& playerPos, class Wanderer& player);
    void spawnBuildings();
    void spawnTowers();
    void addBuilding(const Position& pos, const BeastBuilding& building);
    void addTower(const Position& pos, EnemyTower tower);
    const std::vector<std::pair<Position, BeastBuilding>>& getBuildings() const;
    const std::vector<std::pair<Position, EnemyTower>>& getTowers() const;
};

#endif