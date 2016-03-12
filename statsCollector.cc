#include "statsCollector.h"
#include <iostream>

StatsCollector::StatsCollector(std::string fname): playerProbabilitySum(0),enemyProbabilitySum(0)
{
    Listener in;
    in.setSource(fname);
    while(true)
    {
        DefaultStat* tmp = new DefaultStat();
        tmp->key = in.get<char>();
        if(in.isDone())
        {
            delete tmp;
            break;
        }
        tmp->race = in.get<std::string>();
        tmp->shape = in.get<char>();
        tmp->maxHP = in.get<int>();
        tmp->baseAtk = in.get<int>();
        tmp->baseDef = in.get<int>();
        std::string abilities = in.get<std::string>();
        for(unsigned int i = 0; i < 6; i++)
        {
            tmp->abilities[i] = abilities[i] - '0';
        }
        tmp->probability = in.get<int>();
        tmp->gold = in.get<int>();
        if(tmp->shape == '@'){
            addPlayer(tmp);
            playerProbabilitySum += tmp->probability;
        }
        else if(tmp->race != "")
        {
            addEnemy(tmp);
            enemyProbabilitySum += tmp->probability;
        }
    }
}

StatsCollector::~StatsCollector()
{
    for(unsigned int i = 0; i < playerStat.size(); i++)
    {
        delete playerStat[i];
    }
    for(unsigned int i = 0; i < enemyStat.size(); i++)
    {
        delete enemyStat[i];
    }
}

void StatsCollector::addPlayer(DefaultStat* s)
{
    playerStat.push_back(s);
}

void StatsCollector::addEnemy(DefaultStat* s)
{
    enemyStat.push_back(s);
}

bool StatsCollector::statsExists(std::string type, char key)
{
    if(type == "pc")
    {
        for(unsigned int i = 0; i < playerStat.size(); i++)
        {
            if(key == playerStat[i]->key)
                return true;
        }
    }
    else if(type == "npc")
    {
        for(unsigned int i = 0; i < enemyStat.size(); i++)
        {
            if(key == enemyStat[i]->key)
                return true;
        }
    }
    return false;
}

DefaultStat* StatsCollector::getStats(std::string type, char key)
{
    std::vector<DefaultStat*>* v;
    if(type == "pc")
        v = &playerStat;
    else
        v = &enemyStat;

    for(unsigned int i = 0; i < v->size(); i++)
    {
        if(key == ((*v)[i])->key)
            return (*v)[i];
    }
    return NULL;
}

std::vector<DefaultStat*> StatsCollector::getEnemy()
{
    return enemyStat;
}

std::vector<DefaultStat*> StatsCollector::getPlayer()
{
    return playerStat;
}

std::string StatsCollector::printPlayable() const
{
    std::string out = "";
    for(unsigned int i = 0; i < playerStat.size(); i++)
    {
        std::string race = "";
        for(unsigned int j = 0; j < playerStat[i]->race.length(); j++)
        {
            if(playerStat[i]->race[j] != playerStat[i]->key)
                race += playerStat[i]->race[j];
            else 
            {
                race += '(';
                race += playerStat[i]->race[j];
                race += ')';
            }

        }
        out +=  (i==0?"":", ") + race;
    }
    return out;
}

DefaultStat* StatsCollector::getRandomStat(std::string type)
{
    std::vector<DefaultStat*>* v;
    if(type == "pc") 
        v = &playerStat;
    else 
        v = &enemyStat;
    Randomizer r;
    int race = r.num(0,(type == "pc"?playerProbabilitySum:enemyProbabilitySum));
    for(unsigned int i = 0; i < v->size(); i++)
    {
        if(race < (*v)[i]->probability)
            return (*v)[i];
        race -= (*v)[i]->probability;
    }
    return v->back();
}
