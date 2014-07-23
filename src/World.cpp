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
            int r = rand() % 2;
            if(r == 0) tile = root.tileDatabase()->getTileByName("Dirt");
            else if(r == 1) tile = root.tileDatabase()->getTileByName("Stone");
            m_tiles[x][y] = tile->clone();
        }
    }
    m_camera = Vec2F(154, 154);
    m_forgroundTileLayer = al_create_bitmap(root.windowWidth(), root.windowHeight());
    m_bitmapShifter = new Util::BitmapShifter(root.display(), root.windowWidth(), root.windowHeight());
    m_cameraAtLastRedraw = m_camera - Vec2F(100000, 100000); //so it draw every tile first time
}

World::~World()
{
    for(Tile* tile : m_tiles)
    {
        if(tile != nullptr) delete tile;
    }
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
    return m_tiles[Util::mod(x, m_width)][y];
}
std::vector<Tile*> World::getTiles(int x, int y, int tilesHorizontal, int tilesVertical)
{
    std::vector<Tile*> tiles;
    int firstTileX = x;
    int firstTileY = y;
    int lastTileX = x + tilesHorizontal - 1;
    int lastTileY = x + tilesVertical - 1;
    for(int currentTileX = firstTileX; currentTileX <= lastTileX; ++currentTileX)
    {
        for(int currentTileY = firstTileY; currentTileY <= lastTileY; ++currentTileY)
        {
            Tile* currentTile = getTile(currentTileX, currentTileY);
            if(currentTile) tiles.push_back(currentTile);
        }
    }
    return tiles;
}

Array2<Tile*> World::getTiles2(int x, int y, int tilesHorizontal, int tilesVertical)
{
    Array2<Tile*> tiles(tilesHorizontal, tilesVertical);
    for(int xx = 0; xx < tilesHorizontal; ++xx)
    {
        for(int yy = 0; yy < tilesVertical; ++yy)
        {
            Tile* currentTile = getTile(xx + x, yy + y);
            tiles[xx][yy] = currentTile;
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
    setTile(tile, x, y);
    return true;
}
void World::drawForegroundTileBuffer()
{
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();

    ALLEGRO_DISPLAY* currentDisplay = root.display();
    al_set_target_bitmap(m_forgroundTileLayer);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

    std::sort(m_foregroundTileBuffer.begin(), m_foregroundTileBuffer.end(), [](const DrawableTile & lhs, const DrawableTile & rhs) -> bool {return lhs.spritesheetId < rhs.spritesheetId;});

    std::vector<ALLEGRO_VERTEX> toDraw;
    toDraw.reserve(10000);
    int lastSpritesheetId = m_foregroundTileBuffer[0].spritesheetId;

    for(DrawableTile& tile : m_foregroundTileBuffer)
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

    al_set_target_bitmap(al_get_backbuffer(currentDisplay));
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
void World::drawFromLayerToScreen(ALLEGRO_BITMAP* layer)
{
    al_draw_bitmap(layer, 0, 0, 0);
}
void World::drawMissingForegroundTiles()
{
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();
    int windowWidth = root.windowWidth();
    int windowHeight = root.windowHeight();
    Vec2F worldCoordsTopLeft = screenToWorld(Vec2F(0.0, 0.0));
    Vec2F worldCoordsBottomRight = screenToWorld(Vec2F(windowWidth, windowHeight));
    int firstTileX = Util::fastFloor(worldCoordsTopLeft.x / 16.0f);
    int firstTileY = Util::fastFloor(worldCoordsTopLeft.y / 16.0f);

    int lastTileX = Util::fastFloor(worldCoordsBottomRight.x / 16.0f);
    int lastTileY = Util::fastFloor(worldCoordsBottomRight.y / 16.0f);

    int firstTileToExcludeX = Util::fastFloor(m_cameraAtLastRedraw.x / 16.0f);
    int firstTileToExcludeY = Util::fastFloor(m_cameraAtLastRedraw.y / 16.0f);

    int lastTileToExcludeX = Util::fastFloor((m_cameraAtLastRedraw.x + windowWidth) / 16.0f);
    int lastTileToExcludeY = Util::fastFloor((m_cameraAtLastRedraw.y + windowHeight) / 16.0f);

    Vec2F cameraDiff = m_cameraAtLastRedraw - m_camera;

    if(cameraDiff.x > -0.9) lastTileToExcludeX += 1000; //we down need to draw tiles on left side when we go right etc.
    if(cameraDiff.x < 0.9) firstTileToExcludeX -= 1000;
    if(cameraDiff.y > -0.9) lastTileToExcludeY += 1000;
    if(cameraDiff.y < 0.9) firstTileToExcludeY -= 1000;

    for(int x = firstTileX; x <= lastTileX; ++x) //checking every tile is needed if we want to check whether tile wants an updating draw.
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        { // some ties are not necesserily drawn
            Tile* tile = getTile(x, y);
            if(!tile) continue;
            if(!(x <= firstTileToExcludeX || x >= lastTileToExcludeX || y <= firstTileToExcludeY || y >= lastTileToExcludeY)) continue;
            m_foregroundTileBuffer.push_back(DrawableTile {tile, tile->spritesheetId(), x, y});
        }
    }
}
void World::draw() //in every drawing function coordinates need to be floored, not casted to int
{
    Root& root = Root::instance();

    Vec2F cameraDiff = m_cameraAtLastRedraw - m_camera;

    int shiftX = Util::fastFloor(cameraDiff.x);
    int shiftY = Util::fastFloor(cameraDiff.y);

    m_foregroundTileBuffer.clear();
    m_foregroundTileBuffer.reserve(10000); //need to be reserved better.

    if(shiftX || shiftY) //we want to draw missing tiles only when it is needed
    {
        /* drawing foreground tiles */
        m_bitmapShifter->shift(m_forgroundTileLayer, shiftX, shiftY, al_map_rgba(0, 0, 0, 255));
        drawMissingForegroundTiles();
        drawForegroundTileBuffer();

        m_cameraAtLastRedraw.x -= shiftX;
        m_cameraAtLastRedraw.y -= shiftY;
    }

    //TODO: redrawing tiles that request it

    drawFromLayerToScreen(m_forgroundTileLayer);

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
    return screen + m_camera;
}
Vec2F World::worldToScreen(const Vec2F& world)
{
    return world - m_camera;
}
Vec2F World::camera() const
{
    return m_camera;
}
void World::moveCamera(const Vec2F& diff)
{
    m_camera += diff;
    float xDiff = m_cameraAtLastRedraw.x - m_camera.x;
    m_camera.x = Util::mod(m_camera.x, m_width*16);
    m_cameraAtLastRedraw.x = m_camera.x + xDiff;
}
float World::distance(const Vec2F& a, const Vec2F& b)
{
    float xDiff = b.x - a.x;
    if(abs(xDiff) > m_width*16 / 2.0f) //point is closer in the other way
    {
        xDiff = m_width*16 - xDiff;
    }
    float yDiff = b.y - a.y;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}
Vec2F World::way(const Vec2F& from, const Vec2F& to) //may need fix and there has to be a better name
{
    float xDiff = to.x - from.x;
    if(abs(xDiff) <= m_width*16 / 2.0f)
    {
        return to - from;
    }
    if(to.x < from.x)
    {
        return to - from + Vec2F(m_width*16, 0);
    }
    else
    {
        return to - from - Vec2F(m_width*16, 0);
    }
}
