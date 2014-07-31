#include <iostream>

#include <cstdlib>
#include <algorithm>

#include "Util.h"
#include "World.h"
#include "Root.h"
#include "TileDatabase.h"
#include "SpritesheetDatabase.h"
#include "Tile.h"
#include "WorldGenerator.h"

World::World(WorldGenerator* worldGenerator)
{
    m_worldGenerator = worldGenerator;
    m_width = worldGenerator->worldWidth();
    m_height = worldGenerator->worldHeight();
    m_tiles = Array2<Tile*>(m_width, m_height);

    m_worldGenerator->generate(this);
    // this will be in world generator
    Root& root = Root::instance();
    for(int x = 0; x < m_width; ++x)
    {
        for(int y = 0; y < m_height; ++y)
        {
            Tile* tile = nullptr;
            int r = rand() % 2;
            if(r == 0) tile = root.tileDatabase()->getTileByName("Dirt");
            else if(r == 1) tile = root.tileDatabase()->getTileByName("Stone");
            m_tiles[x][y] = tile->clone();
        }
    }
    //
    m_camera = Vec2F(77, 77);
    m_forgroundTileLayer = al_create_bitmap(root.windowWidth(), root.windowHeight());
    m_forgroundBorderLayer = al_create_bitmap(root.windowWidth(), root.windowHeight());
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
    if(!inWorldRange(x, y)) return nullptr;
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
bool World::inWorldRange(int x, int y)
{
    return (y >= 0 && y < m_height);
}
void World::drawForegroundTileBuffer()
{
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();

    ALLEGRO_DISPLAY* currentDisplay = root.display();
    al_set_target_bitmap(m_forgroundTileLayer);
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO); //may not be needed

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
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
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

    if(cameraDiff.x > -0.9) lastTileToExcludeX += 1000; //we dont need to draw tiles on left side when we go right etc.
    if(cameraDiff.x < 0.9) firstTileToExcludeX -= 1000;
    if(cameraDiff.y > -0.9) lastTileToExcludeY += 1000;
    if(cameraDiff.y < 0.9) firstTileToExcludeY -= 1000;

    for(int x = firstTileX; x <= lastTileX; ++x) //checking every tile is needed if we want to check whether tile wants an updating draw.
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            // some ties are not necesserily drawn
            Tile* tile = getTile(x, y);
            if(!tile) continue;
            if(!(x <= firstTileToExcludeX || x >= lastTileToExcludeX || y <= firstTileToExcludeY || y >= lastTileToExcludeY))
            {
                y = lastTileToExcludeY-1;
                continue;
            }
            m_foregroundTileBuffer.push_back(DrawableTile {tile, tile->spritesheetId(), x, y});
        }
    }
}
void World::drawMissingForgroundBorders()
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

    if(cameraDiff.x > -0.9) lastTileToExcludeX += 1000; //we dont need to draw tiles on left side when we go right etc.
    if(cameraDiff.x < 0.9) firstTileToExcludeX -= 1000;
    if(cameraDiff.y > -0.9) lastTileToExcludeY += 1000;
    if(cameraDiff.y < 0.9) firstTileToExcludeY -= 1000;

    for(int x = firstTileX; x <= lastTileX; ++x) //checking every tile is needed if we want to check whether tile wants an updating draw.
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            // some ties are not necesserily drawn

            Tile* tile = getTile(x, y);

            if(!(x <= firstTileToExcludeX || x >= lastTileToExcludeX || y <= firstTileToExcludeY || y >= lastTileToExcludeY))
            {
                y = lastTileToExcludeY-1;
                continue;
            }

            if(y < -1 || y > m_height) continue; //border has to be drawn outside of world too


            /* to optimize */
            std::vector<DrawableTileBorder> neighbours;
            for(int xx = -1; xx <= 1; ++xx)
            {
                for(int yy = -1; yy <= 1; ++ yy)
                {
                    if(yy == 0 && xx == 0) continue;
                    Tile* currentNeighbourTile = getTile(x+xx, y+yy);
                    if(currentNeighbourTile == nullptr) continue;
                    neighbours.push_back(DrawableTileBorder{currentNeighbourTile, currentNeighbourTile->spritesheetId(), x+xx, y+yy, tile, x, y});
                }
            }
            /* to here */
            size_t numberOfEntries = neighbours.size();
            auto isDuplicatedLater = [&numberOfEntries, &neighbours] (int indexOfCurrent) -> bool
            {
                size_t index = indexOfCurrent+1;
                if(neighbours[indexOfCurrent].tile)
                {
                    int id = neighbours[indexOfCurrent].tile->id();
                    for(;index<numberOfEntries;++index)
                    {
                        DrawableTileBorder& entry = neighbours[index];
                        if(entry.tile)
                        {
                            if(entry.tile->id() == id) return true;
                        }
                    }
                }
                else
                {
                    for(;index<numberOfEntries;++index)
                    {
                        DrawableTileBorder& entry = neighbours[index];
                        if(entry.tile == nullptr) return true;
                    }
                }
                return false;
            };

            for(size_t i = 0; i<numberOfEntries;++i)
            {
                if(isDuplicatedLater(i)) continue;
                m_foregroundBorderBuffer.push_back(neighbours[i]);
            }
        }
    }
}
void World::drawForegroundBorderBuffer()
{
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();

    ALLEGRO_DISPLAY* currentDisplay = root.display();
    al_set_target_bitmap(m_forgroundBorderLayer);
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO); //may not be needed

    std::sort(m_foregroundBorderBuffer.begin(), m_foregroundBorderBuffer.end(), [](const DrawableTileBorder & lhs, const DrawableTileBorder & rhs) -> bool {return lhs.spritesheetId < rhs.spritesheetId;});

    std::vector<ALLEGRO_VERTEX> toDraw;
    toDraw.reserve(10000);
    int lastSpritesheetId = m_foregroundBorderBuffer[0].spritesheetId;

    for(DrawableTileBorder& tile : m_foregroundBorderBuffer)
    {
        int currentSpritesheetId = tile.spritesheetId;
        if(currentSpritesheetId != lastSpritesheetId)
        {
            al_draw_prim(&(toDraw[0]), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
            toDraw.clear();
            toDraw.reserve(10000);
            lastSpritesheetId = currentSpritesheetId;
        }
        tile.tile->drawOuter(this, toDraw, tile.x, tile.y, tile.destX, tile.destY, tile.destTile);
    }
    if(toDraw.size()) al_draw_prim(&(toDraw[0]), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    al_set_target_bitmap(al_get_backbuffer(currentDisplay));
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
void World::draw() //in every drawing function coordinates need to be floored, not casted to int
{
    Root& root = Root::instance();

    Vec2F cameraDiff = m_cameraAtLastRedraw - m_camera;

    int shiftX = Util::fastFloor(cameraDiff.x);
    int shiftY = Util::fastFloor(cameraDiff.y);

    m_foregroundTileBuffer.clear();
    m_foregroundTileBuffer.reserve(10000); //need to be reserved better.

    m_foregroundBorderBuffer.clear();
    m_foregroundBorderBuffer.reserve(10000); //need to be reserved better.

    if(shiftX || shiftY) //we want to draw missing tiles only when it is needed
    {
        /* drawing foreground tiles */
        m_bitmapShifter->shift(m_forgroundTileLayer, shiftX, shiftY, al_map_rgba(0, 0, 0, 0));
        m_bitmapShifter->shift(m_forgroundBorderLayer, shiftX, shiftY, al_map_rgba(0, 0, 0, 0)); //when shifting fps drops from 1500 to about 50-200. That's unacceptable.

        drawMissingForegroundTiles();
        drawMissingForgroundBorders();

        drawForegroundTileBuffer();
        drawForegroundBorderBuffer();

        m_cameraAtLastRedraw.x -= shiftX;
        m_cameraAtLastRedraw.y -= shiftY;
    }

    //TODO: redrawing tiles that request it

    drawFromLayerToScreen(m_forgroundTileLayer);
    drawFromLayerToScreen(m_forgroundBorderLayer);

}
void World::update()
{
    //m_tiles[5][4]->update(this, 5, 4);
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
WorldGenerator* World::worldGenerator() const
{
    return m_worldGenerator;
}
void World::moveCamera(const Vec2F& diff)
{
    m_camera += diff;
    float xDiff = m_cameraAtLastRedraw.x - m_camera.x;
    m_camera.x = Util::mod(m_camera.x, m_width * 16);
    m_cameraAtLastRedraw.x = m_camera.x + xDiff;
}
float World::distance(const Vec2F& a, const Vec2F& b)
{
    float xDiff = b.x - a.x;
    if(abs(xDiff) > m_width * 16 / 2.0f) //point is closer in the other way
    {
        xDiff = m_width * 16 - xDiff;
    }
    float yDiff = b.y - a.y;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}
Vec2F World::way(const Vec2F& from, const Vec2F& to) //may need fix and there has to be a better name
{
    float xDiff = to.x - from.x;
    if(abs(xDiff) <= m_width * 16 / 2.0f)
    {
        return to - from;
    }
    if(to.x < from.x)
    {
        return to - from + Vec2F(m_width * 16, 0);
    }
    else
    {
        return to - from - Vec2F(m_width * 16, 0);
    }
}
