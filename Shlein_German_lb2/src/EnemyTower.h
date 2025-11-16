#ifndef ENEMY_TOWER_H
#define ENEMY_TOWER_H

#include "GameField.h"

class EnemyTower {
private:
    int attackRange;
    int damage;
    int attackCooldown;
    int currentCooldown;
    bool isActive;

public:
    EnemyTower(int range = 4, int damage = 15, int cooldown = 3);
    
    void update();
    bool canAttack() const;
    void performAttack(const Position& towerPos, const Position& playerPos, GameField& field, class Wanderer& player);
    bool isInRange(const Position& towerPos, const Position& targetPos) const;
    
    bool getIsActive() const;
    void setActive(bool active);
    int getAttackRange() const;
};

#endif