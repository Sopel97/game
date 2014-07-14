#include <iostream>
#include "World.h"
#include "Root.h"
#include "TileDatabase.h"
#include "SpritesheetDatabase.h"

World::World(int width, int height) :
    m_width(width),
    m_height(height)
{
    m_tiles = Array2<Tile*>(width, height);
    Root& root = Root::instance();
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            Tile* tile = root.tileDatabase()->getTileByName("Dirt");
            m_tiles[x][y] = tile->clone();
        }
    }
    m_camera = Vec2F(154,154);
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
    Root& root = Root::instance();
    std::vector<ALLEGRO_VERTEX> toDraw; //can't think of a name

    Vec2F worldCoordsTopLeft = screenToWorld(Vec2F(0.0, 0.0));
    Vec2F worldCoordsBottomRight = screenToWorld(Vec2F(1024.0, 768.0));
    int firstTileX = worldCoordsTopLeft.x/16.0f;
    int firstTileY = worldCoordsTopLeft.y/16.0f;

    int lastTileX = worldCoordsBottomRight.x/16.0f+1;
    int lastTileY = worldCoordsBottomRight.y/16.0f+1;
    for(int x = firstTileX; x <= lastTileX; ++x)
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            getTile(x,y)->drawInner(this, toDraw, x, y);
        }
    }
    al_draw_prim(&(toDraw[0]), NULL, root.spritesheetDatabase()->getSpritesheetByName("dirt.png"), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}
void World::update()
{
    m_tiles[5][4]->update(this, 5, 4);
}
void World::doRandomTileUpdate()
{

}
void World::doConstantTileUpdate()
{

}
Vec2F World::screenToWorld(const Vec2F& screen)
{
    return screen+m_camera;
}
Vec2F World::worldToScreen(const Vec2F& world)
{
    return world-m_camera;
}
Vec2F World::camera() const
{
    return m_camera;
}
