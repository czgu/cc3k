#ifndef _DEFAULTSTAT_H
#define _DEFAULTSTAT_H

#include <string>

struct DefaultStat
{
    char key;
    std::string race;
    char shape;
    int maxHP;
    int baseAtk;
    int baseDef;
    int abilities[6];
    int probability;
    int gold;
};

#endif
