CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = game
OBJS = main.o GameField.o Wanderer.o Beast.o BeastBuilding.o GameController.o \
       BeastManager.o BuildingManager.o CombatManager.o InputHandler.o \
       Spell.o DirectDamageSpell.o AreaSpell.o Hand.o SpellFactory.o TrapSpell.o EnemyTower.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp GameController.h
	$(CXX) $(CXXFLAGS) -c main.cpp

GameField.o: GameField.cpp GameField.h
	$(CXX) $(CXXFLAGS) -c GameField.cpp

Wanderer.o: Wanderer.cpp Wanderer.h Hand.h
	$(CXX) $(CXXFLAGS) -c Wanderer.cpp

Beast.o: Beast.cpp Beast.h
	$(CXX) $(CXXFLAGS) -c Beast.cpp

BeastBuilding.o: BeastBuilding.cpp BeastBuilding.h
	$(CXX) $(CXXFLAGS) -c BeastBuilding.cpp

GameController.o: GameController.cpp GameController.h BeastManager.h BuildingManager.h CombatManager.h InputHandler.h SpellFactory.h
	$(CXX) $(CXXFLAGS) -c GameController.cpp

BeastManager.o: BeastManager.cpp BeastManager.h
	$(CXX) $(CXXFLAGS) -c BeastManager.cpp

BuildingManager.o: BuildingManager.cpp BuildingManager.h EnemyTower.h
	$(CXX) $(CXXFLAGS) -c BuildingManager.cpp

CombatManager.o: CombatManager.cpp CombatManager.h
	$(CXX) $(CXXFLAGS) -c CombatManager.cpp

InputHandler.o: InputHandler.cpp InputHandler.h Spell.h
	$(CXX) $(CXXFLAGS) -c InputHandler.cpp

Spell.o: Spell.cpp Spell.h
	$(CXX) $(CXXFLAGS) -c Spell.cpp

Hand.o: Hand.cpp Hand.h Spell.h
	$(CXX) $(CXXFLAGS) -c Hand.cpp

DirectDamageSpell.o: DirectDamageSpell.cpp DirectDamageSpell.h Spell.h
	$(CXX) $(CXXFLAGS) -c DirectDamageSpell.cpp

AreaSpell.o: AreaSpell.cpp AreaSpell.h Spell.h
	$(CXX) $(CXXFLAGS) -c AreaSpell.cpp

SpellFactory.o: SpellFactory.cpp SpellFactory.h DirectDamageSpell.h AreaSpell.h TrapSpell.h
	$(CXX) $(CXXFLAGS) -c SpellFactory.cpp

TrapSpell.o: TrapSpell.cpp TrapSpell.h Spell.h
	$(CXX) $(CXXFLAGS) -c TrapSpell.cpp

EnemyTower.o: EnemyTower.cpp EnemyTower.h
	$(CXX) $(CXXFLAGS) -c EnemyTower.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean