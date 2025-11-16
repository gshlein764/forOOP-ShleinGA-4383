#include "BuildingManager.h"
#include "Wanderer.h"
#include <random>
#include <iostream>

BuildingManager::BuildingManager(GameField& field, BeastManager& beastManager)
    : field(field), beastManager(beastManager) {}

void BuildingManager::updateBuildings() {
    for (auto& buildingData : buildings) {
        buildingData.second.update();
        if (buildingData.second.shouldSpawnEnemy()) {
            Position buildingPos = buildingData.first;
            
            std::vector<Position> adjacentPositions = {
                Position(buildingPos.x + 1, buildingPos.y),
                Position(buildingPos.x - 1, buildingPos.y),
                Position(buildingPos.x, buildingPos.y + 1),
                Position(buildingPos.x, buildingPos.y - 1)
            };
            
            for (const auto& pos : adjacentPositions) {
                if (field.isCellPassable(pos.x, pos.y) && field.getCell(pos.x, pos.y).isEmpty()) {
                    Beast beast(30, 10);
                    beastManager.addBeast(pos, Beast(50, 10)); // Пример параметров
                    std::cout << "Beast building spawned a new enemy!\n";
                    break;
                }
            }
        }
    }
}

void BuildingManager::updateTowers(const Position& playerPos, Wanderer& player) {
    for (auto& towerData : towers) {
        towerData.second.update();
        if (towerData.second.canAttack()) {
            towerData.second.performAttack(towerData.first, playerPos, field, player);
        }
    }
}

void BuildingManager::spawnBuildings() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> intervalDis(6, 8);

    for (int i = 0; i < 1; ++i) {
        int x, y;
        if (field.findEmptyPosition(x, y)) {
            BeastBuilding building(intervalDis(gen));
            addBuilding(Position(x, y), building);
        }
    }
}

void BuildingManager::spawnTowers() {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < 2; ++i) {
        int x, y;
        if (field.findEmptyPosition(x, y)) {
            addTower(Position(x, y), EnemyTower(4, 15, 3));
        }
    }
}

void BuildingManager::addBuilding(const Position& pos, const BeastBuilding& building) {
    buildings.emplace_back(pos, building);
    field.getCell(pos.x, pos.y).setHasBuilding(true);
}

void BuildingManager::addTower(const Position& pos, EnemyTower tower) {
    towers.emplace_back(pos, tower);
    field.getCell(pos.x, pos.y).setHasBuilding(true);
}

const std::vector<std::pair<Position, BeastBuilding>>& BuildingManager::getBuildings() const {
    return buildings;
}

const std::vector<std::pair<Position, EnemyTower>>& BuildingManager::getTowers() const {
    return towers;
}