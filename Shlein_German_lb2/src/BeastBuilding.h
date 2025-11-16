#ifndef BEASTBUILDING_H
#define BEASTBUILDING_H

class BeastBuilding {
    private:
        int spawnCounter;
        int spawnInterval;
        bool isActive;
    public:
        BeastBuilding(int interval = 10);

        bool shouldSpawnEnemy() const;
        void update();
        
        bool getIsActive() const;
        void setActive(bool active);
};

#endif