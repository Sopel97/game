#include <iostream>
#include "World.h"

World::World(int width, int height) :
    m_width(width),
    m_height(height)
{

}

World::~World()
{
    //deleting tiles
}
int World::width()
{
    return m_width;
}
int World::height()
{
    return m_height;
}
Tile* World::getTile(int x, int y)
{
    return m_tiles[x][y];
}
std::vector<Tile*> World::getTiles(int x, int y, int tilesHorizontal, int tilesVertical)
{
    std::vector<Tile*> tiles;
    int firstTileX = x;
    int firstTileY = y;
    int lastTileX = x+tilesHorizontal-1;
    int lastTileY = x+tilesVertical-1;
    for(int currentTileX = firstTileX;currentTileX<=lastTileX;++currentTileX)
    {
        for(int currentTileY = firstTileY;currentTileY<=lastTileY;++currentTileY)
        {
            Tile* currentTile = getTile(currentTileX, currentTileY);
            if(currentTile) tiles.push_back(currentTile);
        }
    }
    return tiles;
}

void World::setTile(Tile* tile, int x, int y)
{
    m_tiles[x][y] = tile;
}
bool World::placeTile(Tile* tile, int x, int y)
{
    //for now just setting tile, but needs some checking done
    setTile(tile, x,y);
    return true;
}

void World::draw()
{
    //std::cout << "draw\n";
}
void World::update()
{
    //std::cout << "update\n";
}
void World::doRandomTileUpdate()
{

}
void World::doConstantTileUpdate()
{

}
