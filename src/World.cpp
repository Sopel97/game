#include <iostream>

#include <cstdlib>
#include <algorithm>

#include "Util.h"
#include "World.h"
#include "Root.h"
#include "TileDatabase.h"
#include "SpritesheetDatabase.h"
#include "Tile.h"

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
            Tile* tile = nullptr;
            int r = rand()%2;
            if(r == 0) tile = root.tileDatabase()->getTileByName("Dirt");
            else if(r == 1) tile = root.tileDatabase()->getTileByName("Stone");
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
    if(y < 0 || y >= m_height) return nullptr;
    return m_tiles[Util::mod(x,m_width)][y];
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
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();
    int windowWidth = root.windowWidth();
    int windowHeight = root.windowHeight();
    Vec2F worldCoordsTopLeft = screenToWorld(Vec2F(0.0, 0.0));
    Vec2F worldCoordsBottomRight = screenToWorld(Vec2F(windowWidth, windowHeight)); //make ot so it takes from window size
    int firstTileX = Util::fastFloor(worldCoordsTopLeft.x/16.0f);
    int firstTileY = Util::fastFloor(worldCoordsTopLeft.y/16.0f);

    int lastTileX = Util::fastFloor(worldCoordsBottomRight.x/16.0f+1.0f);
    int lastTileY = Util::fastFloor(worldCoordsBottomRight.y/16.0f+1.0f);

    struct DrawableTile
    {
        Tile* tile;
        int spritesheetId;
        int x;
        int y;
    };

    std::vector<DrawableTile> drawableTiles;
    drawableTiles.reserve((lastTileX-firstTileX+1)*(lastTileY-firstTileY+1));
    for(int x = firstTileX; x <= lastTileX; ++x)
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            Tile* tile = getTile(x,y);
            if(!tile) continue;
            drawableTiles.push_back(DrawableTile{tile, tile->spritesheetId(), x, y});
        }
    }
    std::sort(drawableTiles.begin(), drawableTiles.end(), [](const DrawableTile& lhs, const DrawableTile& rhs) -> bool {return lhs.spritesheetId < rhs.spritesheetId;});

    std::vector<ALLEGRO_VERTEX> toDraw;
    toDraw.reserve(10000);
    int lastSpritesheetId = drawableTiles[0].spritesheetId;
    for(DrawableTile& tile : drawableTiles)
    {
        int currentSpritesheetId = tile.spritesheetId;
        if(currentSpritesheetId != lastSpritesheetId)
        {
            al_draw_prim(&(toDraw[0]), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
            toDraw.clear();
            toDraw.reserve(10000);
            lastSpritesheetId = currentSpritesheetId;
        }
        tile.tile->drawInner(this, toDraw, tile.x, tile.y);
    }
    if(toDraw.size()) al_draw_prim(&(toDraw[0]), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
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
void World::moveCamera(const Vec2F& diff)
{
    m_camera += diff;
}
