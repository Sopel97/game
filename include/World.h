#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Array2.h"
class Tile;

class World
{
public:
    World(int width, int height);
    virtual ~World();

    int width();
    int height();

    Tile* getTile(int x, int y);
    std::vector<Tile*> getTiles(int x, int y, int tilesHorizontal, int tilesVertical);

    void setTile(Tile* tile, int x, int y);  //setting tile doesn't check if it's possible
    bool placeTile(Tile* tile, int x, int y);

    void draw();
    void update();
    void doRandomTileUpdate();
    void doConstantTileUpdate();

protected:
private:
    int m_width;
    int m_height;
    Array2<Tile*> m_tiles;
};

#endif // WORLD_H
