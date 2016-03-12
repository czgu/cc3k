#include "mapGenerator.h"
#include <iostream>
#include <map>
#include <vector>

Floor* MapGenerator::createMap(std::string fname,Player *p, StatsCollector* s,int currLevel, int enemySize, int potionSize,int goldSize, std::vector<int>& potionSetting, std::vector<Tuple>& goldSetting)
{
    Listener tmp;
    tmp.setSource(fname);
    int row = tmp.get<int>();
    int col = tmp.get<int>();
    int roomNum = tmp.get<int>();
    std::vector<Coord>* chambers = new std::vector<Coord>[roomNum];
    Floor* floor = addObjects(mapRead(tmp,row,col,roomNum,chambers),p,chambers,roomNum,s,currLevel,enemySize,potionSize,goldSize,potionSetting,goldSetting);

    delete [] chambers;
    return floor;
}

Floor* MapGenerator::mapRead(Listener& in,int row, int col,int roomNum,std::vector<Coord>* chambers)
{
    Terrain** terrain = new Terrain*[row];
    for(int i = 0; i < row; i++)
    {
        terrain[i] = new Terrain[col];
        for(int j = 0; j < col; j++)
        {
            char n = in.getChar();
            if(n == '\n') n = in.getChar();
            switch(n)
            {
                case ' ':
                    terrain[i][j] = EMPTY;
                    break;
                case '|':
                    terrain[i][j] = WALLV;
                    break;
                case '-':
                    terrain[i][j] = WALLH;
                    break;
                case '#':
                    terrain[i][j] = HALL;
                    break;
                case '+':
                    terrain[i][j] = DOOR;
                    break;
                default:
                    int currRoom = n - '0';
                    if( currRoom <= roomNum && roomNum >= 0)
                    {
                        Coord p = {i,j};
                        chambers[currRoom-1].push_back(p);
                        terrain[i][j] = SPOT;
                    }
                    break;
            }
        }     
    }
    Floor* floor = new Floor(row,col,terrain);
    for(int i = 0; i < row; i++)
        delete [] terrain[i];
    delete [] terrain;
        return floor;
}

Floor* MapGenerator::addObjects(Floor* basicFloor,Player *p,std::vector<Coord>* chambers,  int roomNum, StatsCollector* s, int currLevel, int enemySize, int potionSize,int goldSize,std::vector<int>& potionSetting, std::vector<Tuple>& goldSetting)
{
    Randomizer r;
    int currRoom;
    int currTile;
    //add the player and stairs
    r.createRandomSeq(1,roomNum,2,true);
    currRoom = r.getFirstNum();
    currTile = r.num(0,chambers[currRoom-1].size()-1);
    
    p->setLocation(chambers[currRoom-1][currTile],basicFloor->getTile(chambers[currRoom-1][currTile]));
    
    //set stairs and add to floor
    currRoom = r.getFirstNum();
    currTile =  r.num(0,chambers[currRoom-1].size()-1);
    
    Stairs* stair = new Stairs();
    stair->setLocation(chambers[currRoom-1][currTile],basicFloor->getTile(chambers[currRoom-1][currTile]));
    basicFloor->setStairs(stair);
    //add the enemy
    while(enemySize+potionSize+goldSize > basicFloor->enemySize()+basicFloor->itemSize())
    {
        
        currRoom = r.num(1,roomNum);
        currTile = r.num(0,chambers[currRoom-1].size()-1);
        
        Coord p = chambers[currRoom-1][currTile];    
        Tile* t = basicFloor->getTile(p); 
        if(!t->hasSomethingOn())
        {
            Object* o;

            if(basicFloor->itemSize() < goldSize)
            {
                int goldNum = r.num(1,goldSetting.back().first);
                for(unsigned int i = 0; i < goldSetting.size(); i++)
                {

                    if(i == goldSetting.size() - 1)
                    {
                        r.createRandomSeq(0,7,5,true);
                        int bound = r.stackSize();
                        for(int j = 0; j < bound; j++)
                        {
                            Tile* t2 = t->getNeighbour(r.getFirstNum());
                            if(t2 && t2->isGeneratable())
                            {
                                NPC* dragon = new NPC( s->getStats("npc",'D' ) ,currLevel);        
                                Coord empty = {0,0};
                                dragon->setLocation(empty,t2);
                                basicFloor->setNPC(dragon);
                                o = new Hoard( goldSetting[i].second, dragon );
                                break;
                            }
                        }
                        break;
                    }
                    else if(goldNum <= goldSetting[i].first)
                    {
                        o = new Gold(goldSetting[i].second);
                        break;
                    }
                }
                basicFloor->setItem(static_cast<Item*>(o));
            }
            else if(basicFloor->itemSize() < goldSize+potionSize)
            {
                int potionNum = r.num(0,potionSetting.size() - 1);
                int rnd = r.num(0,1);
                o = new Potion(static_cast<PotionEffect>(potionNum),potionSetting[potionNum]*(rnd==0?1:-1));
                basicFloor->setItem(static_cast<Item*>(o));
            }           
            else if(basicFloor->enemySize() < enemySize)
            {
                o = new NPC( s->getRandomStat("npc"), currLevel );
                basicFloor->setNPC(static_cast<NPC*>(o));
            }

            o->setLocation(p,t);
        }
    }   
    return basicFloor;
}

Floor* MapGenerator::createStaticMap(Listener &in, Player *p, StatsCollector* s,int currLevel, std::vector<int>& potionSetting, std::vector<Tuple>&goldSetting)
{
    char theGrid[25][79];
    Terrain** terrain = new Terrain*[25];
    for(int i = 0; i < 25; i++)
    {  
        terrain[i] = new Terrain[79];
        for(int j = 0; j < 79; j++)
        {
            theGrid[i][j] = ' ';
            char n = in.getChar();
            if(n == '\n') n = in.getChar();
            std::cout << n << std::endl;
            switch(n)
            {
                case ' ':
                    terrain[i][j] = EMPTY;
                    break;
                case '|':
                    terrain[i][j] = WALLV;
                    break;
                case '-':
                    terrain[i][j] = WALLH;
                    break;
                case '#':
                    terrain[i][j] = HALL;
                    break;
                case '+':
                    terrain[i][j] = DOOR;
                    break;
                default:
                    theGrid[i][j] = n;
                    terrain[i][j] = SPOT;
            }   
        }
        std::cout << "\n";       
    }
    Floor* f = new Floor(25,79,terrain); 
    std::vector<Coord> dHoard;
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 79; j++)
        {
            if(theGrid[i][j] != ' ')
            {   
                Coord c = {i,j};
                Tile* t = f->getTile(c);
                if(s->statsExists("npc",theGrid[i][j]) && theGrid[i][j] != 'D') //enemy
                {
                    NPC *e = new NPC( s->getStats("npc",theGrid[i][j]),currLevel);
                    e->setLocation(c,t);
                    f->setNPC(e);
                }
                else if(theGrid[i][j] == '@') //player
                {
                    p->setLocation(c,t);
                }
                else if(theGrid[i][j] == '\\') //stairs
                {
                    Stairs* stair = new Stairs();
                    stair->setLocation(c,t);
                    f->setStairs(stair);
                }
                else
                {
                    Object* o;
                    unsigned int n = theGrid[i][j] - '0';
                    if(n < 6) //potion
                    {
                        o = new Potion(static_cast<PotionEffect>(n%3),potionSetting[n%3] * (n < 3?1:-1));
                    }
                    else if(n < 9) //normal gold
                    {
                        o = new Gold(goldSetting[n-6].second);
                    }
                    else if(n == 9)//dragon hoard
                    {
                        dHoard.push_back(c);
                    }
                    if(n < 9)
                    {
                        o->setLocation(c,t);
                        f->setItem(static_cast<Item*>(o));
                    }
                }
            }
        }
    }
    for(unsigned int i = 0; i < dHoard.size(); i++)
    {
        Coord c = dHoard[i];
        Tile* t = f->getTile(c);
        NPC *dragon = NULL;
        for(int j = c.row-1; j <= c.row+1; j++)
        {
            for(int k = c.col-1; k <= c.col+1;k++)
            {
                if(j>=0 && j < 25 && k>=0 && k < 79 && ( j != c.row || k != c.col))
                {
                    Coord c2 = {j,k};
                    Tile *t2 = f->getTile(c2);
                    if(theGrid[j][k] == 'D' && t2->isGeneratable())
                    {
                        dragon = new NPC( s->getStats("NPC",'D' ),currLevel);
                        dragon->setLocation(c2,t2);
                        f->setNPC(dragon);
                        break;
                    } 
                }
            }
            if(dragon) break;
        }
        if(dragon)
        {
            Item* o = new Hoard( goldSetting[3].second, dragon);
            o->setLocation(c,t);
            f->setItem(o);
        }
    }
    for(int i = 0; i < 25; i++)
        delete [] terrain[i];
    delete [] terrain;

    return f;
}
