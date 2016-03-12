#ifndef _TILE_H
#define _TILE_H

class Object;
class Character;
class PlayerImpl;

enum Terrain
{
    EMPTY = 0,
    WALLV,
    WALLH,
    HALL,
    DOOR,
    SPOT
};


class Tile
{
    Terrain terrain;
    Object* contains;
    Tile* neighbours[8];
    int nNeighbours;
    
    
    public:
    Tile();
    Tile( Terrain );
    ~Tile();

    void setTerrain( Terrain );

    bool isPassable( const Character& ) const;
    bool hasSomethingOn() const;
    void addNeighbour( Tile* );
    void notifyEnemies( PlayerImpl& );
    void notifyEnemy( PlayerImpl& );

    Object* replaceObject( Object* );
    Object* getObject();
    void removeObject();

    char draw() const;

    Tile* getNeighbour(int i);
    bool isGeneratable();
};

#endif
