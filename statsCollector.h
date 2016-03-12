#ifndef _STATSCOLLECTOR_H
#define _STATSCOLLECTOR_H

#include "defaultStat.h"
#include <string>
#include <vector>
#include "listener.h"
#include "randomizer.h"

class StatsCollector
{
    std::vector<DefaultStat*> playerStat;
    std::vector<DefaultStat*> enemyStat;
    int playerProbabilitySum;
    int enemyProbabilitySum;
    void addPlayer(DefaultStat* s);
    void addEnemy(DefaultStat* s); 
 public:
    StatsCollector(std::string fname);
    ~StatsCollector();   
    bool statsExists(std::string type, char key);
    DefaultStat* getStats(std::string type, char key);
    std::vector<DefaultStat*> getEnemy();
    std::vector<DefaultStat*> getPlayer();
    std::string printPlayable() const;
    DefaultStat* getRandomStat(std::string type);
};

#endif
