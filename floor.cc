#include "floor.h"
#include <iostream>

Floor::Floor(int row, int col, Terrain ** terrain):
ROW(row),COL(col),nextFloor(false),stair(NULL)
{
    theGrid = new Tile*[ROW];
    for(int i = 0; i < ROW; i++)
    {
        theGrid[i] = new Tile[COL];
        for(int j = 0; j < COL; j++)
        {
            theGrid[i][j].setTerrain(terrain[i][j]);
                       
        }
    }
    for(int i = 0; i <ROW; i++)
        for(int j = 0; j < COL; j++)
            addNeighbour(i,j); 
}

Floor::~Floor()
{
    delete stair;
    for(unsigned int i = 0; i < enemy.size(); i++)
    {
        delete enemy[i];
    }
    for(unsigned int i = 0; i < item.size(); i++)
    {
        delete item[i];
    }
    for(int i = 0; i < ROW; i++)
        delete [] theGrid[i];
    delete [] theGrid;
}

void Floor::draw(BoardDisplay& display)
{
   for(int i = 0; i < ROW; i++)
   {
        for(int j = 0; j < COL; j++)
        {
            display.draw(i,j,theGrid[i][j].draw());
        }
    }
}

Tile* Floor::getTile(Coord p)
{
    if(p.row >= ROW || p.row < 0 || p.col >= COL || p.col < 0)
        return NULL;
    return &theGrid[p.row][p.col];
}

void Floor::update()
{
    for(unsigned int i = 0; i < enemy.size(); i++)
    {
        if(enemy[i]->isAlive())
            enemy[i]->update();
    }
}

bool Floor::levelDone()
{
    return stair->isReached();
}

void Floor::setNPC(NPC *s)
{
    enemy.push_back(s);
}

void Floor::addNeighbour(int r, int c)
{
    for(int i = r-1; i <= r+1; i++)
    {
        for(int j = c-1; j <= c+1;j++)
        {
            //add all neighbours in the valid position
            if(i>=0 && i < ROW && j>=0 && j < COL && ( i != r || j !=  c))
            {
                theGrid[r][c].addNeighbour(&theGrid[i][j]);
            }
        }
    }
}

void Floor::setStairs(Stairs* s)
{
    stair = s;
}

void Floor::setItem(Item* i)
{
    item.push_back(i);
}

int Floor::enemySize()
{ 
    return static_cast<int>(enemy.size());
}

int Floor::itemSize()
{
    return static_cast<int>(item.size());
}

