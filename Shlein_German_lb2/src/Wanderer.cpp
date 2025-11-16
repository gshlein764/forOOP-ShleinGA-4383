#include "Wanderer.h"
#include <iostream>

Wanderer::Wanderer() 
    : hp(100), maxHp(100), meleeDamage(20), rangeDamage(15), shield(20),
      maxShield(20), shieldRegen(2), points(0), lvl(1), exp(0), expToNextLvl(100),
      combatMode(CombatMode::MELEE), isAlive(true),
      mana(50), maxMana(50), manaRegen(10), hand(3) {}
    
void Wanderer::takeDamage(int damageAmount) {
    if (!isAlive) return;
    
    int actualDamage = damageAmount;
    if (shield > 0) {
        int shieldDamage = std::min(shield, actualDamage);
        shield -= shieldDamage;
        actualDamage -= shieldDamage;
        
        std::cout << "Shield absorbed " << shieldDamage << " damage! ";
        if (shield == 0) {
            std::cout << "Shield broken! ";
        }
    }
    
    if (actualDamage > 0) {
        hp -= actualDamage;
        std::cout << "Took " << actualDamage << " health damage! ";
    }
    
    if (hp <= 0) {
        hp = 0;
        die();
    }
    
    std::cout << "Health: " << hp << "/" << maxHp << " | Shield: " << shield << "/" << maxShield << "\n";
}

void Wanderer::heal(int healAmount) {
    hp = std::min(hp + healAmount, maxHp);
}

void Wanderer::regenerateShield() {
    if (shield < maxShield) {
        shield = std::min(shield + 4, maxShield);
    }
}

void Wanderer::addPoints(int pointsToAdd) {
    points += pointsToAdd;
}

void Wanderer::addExp(int expToAdd) {
    exp += expToAdd;
    while (exp >= expToNextLvl) {
        lvlUp();
    }
}

bool Wanderer::spendMana(int amount) {
    if (mana >= amount) {
        mana -= amount;
        return true;
    }
    return false;
}

void Wanderer::regenerateMana() {
    mana = std::min(mana + manaRegen, maxMana);
}

void Wanderer::addMana(int amount) {
    mana = std::min(mana + amount, maxMana);
}

Hand& Wanderer::getHand() {
    return hand;
}

const Hand& Wanderer::getHand() const {
    return hand;
}

bool Wanderer::learnSpell(std::unique_ptr<SpellCard> spell) {
    return hand.addSpell(std::move(spell));
}

void Wanderer::switchCombatMode() {
    combatMode = (combatMode == CombatMode::MELEE) ? CombatMode::RANGED : CombatMode::MELEE;
}

void Wanderer::lvlUp() {
    lvl++;
    exp -= expToNextLvl;
    expToNextLvl = expToNextLvl * 3 / 2;

    maxHp += 15;
    hp = maxHp;
    meleeDamage += 5;
    rangeDamage += 3;
    maxShield += 3;
    shield = maxShield;
    shieldRegen += 1;
    maxMana += 10;
    mana = maxMana;
    manaRegen += 1;

    std::cout<< "Congratulations, you have reached a new level! Now your level " << lvl << "!\n";
    std::cout << "Shield upgraded to " << maxShield << "!\n";
    std::cout << "Mana upgraded to " << maxMana << "!\n";
}

void Wanderer::die() {
    isAlive = false;
    std::cout << "Wanderer has died!:(\n";
}

int Wanderer::getHealth() const { return hp; }
int Wanderer::getMaxHealth() const { return maxHp; }
int Wanderer::getDamage() const { return getCurrentDamage(); }
int Wanderer::getShield() const { return shield; }
int Wanderer::getMaxShield() const { return maxShield; }
int Wanderer::getPoints() const { return points; }
int Wanderer::getLvl() const { return lvl; }
int Wanderer::getExp() const { return exp; }
int Wanderer::getExpToNextLvl() const { return expToNextLvl; }
int Wanderer::getMana() const { return mana; }
int Wanderer::getMaxMana() const { return maxMana; }
CombatMode Wanderer::getCombatMode() const { return combatMode; }
bool Wanderer::getIsAlive() const { return isAlive; }

int Wanderer::getCurrentDamage() const {
    return (combatMode == CombatMode::MELEE) ? meleeDamage : rangeDamage;
}

void Wanderer::displayStatus() const {
    std::cout << "=== Wanderer Status ===\n"
              << "Health: " << hp << "/" << maxHp << " | Shield: " << shield << "/" << maxShield << "\n"
              << "Level: " << lvl << " | Exp: " << exp << "/" << expToNextLvl << "\n"
              << "Damage: " << getCurrentDamage() << " | Shield Regen: " << shieldRegen << "\n"
              << "Combat Mode: " << (combatMode == CombatMode::MELEE ? "MELEE" : "RANGED") << "\n"
              << "Points: " << points << "\n";
}