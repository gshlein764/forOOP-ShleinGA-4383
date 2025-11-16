#include "BeastBuilding.h"

BeastBuilding::BeastBuilding(int interval)
    : spawnCounter(0), spawnInterval(interval), isActive(true) {}
    
bool BeastBuilding::shouldSpawnEnemy() const {
    return spawnCounter >= spawnInterval;
}

void BeastBuilding::update() {
    if (isActive) {
        spawnCounter++;
    }
}

bool BeastBuilding::getIsActive() const {
    return isActive;
}

void BeastBuilding::setActive(bool active) {
    isActive = active;
}