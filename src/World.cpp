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
    m_tiles = Array2<Tile*>(m_width, m_height, nullptr);
    m_worldGenerator->generate(this);
    // this will be in world generator
    Root& root = Root::instance();
    /*for(int x = 0; x < m_width; ++x)
    {
        for(int y = 0; y < m_height; ++y)
        {
            Tile* tile = nullptr;
            int r = rand() % 2;
            if(r == 0) tile = root.tileDatabase()->getTileByName("Dirt");
            else if(r == 1) tile = root.tileDatabase()->getTileByName("Stone");
            m_tiles[x][y] = tile->clone();
        }
    }*/
    //
    m_camera = Vec2D(77.001, 77.001);
    m_foregroundTileLayer = al_create_bitmap(root.windowWidth(), root.windowHeight());
    m_foregroundBorderLayer = al_create_bitmap(root.windowWidth(), root.windowHeight());
    m_bitmapShifter = new Util::BitmapShifter(root.display(), root.windowWidth(), root.windowHeight());
    m_cameraAtLastRedraw = Vec2I(1000000, -1000000); //so it draw every tile first time
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

bool World::setTile(Tile* tile, int x, int y)
{
    if(!inWorldRange(x, y)) return false;
    x = Util::mod(x, m_width);
    if(m_tiles[x][y]) delete m_tiles[x][y];
    m_tiles[x][y] = tile;
    return true;
}
bool World::placeTile(Tile* tile, int x, int y, bool update, bool redraw)
{
    if(!inWorldRange(x, y)) return false;
    x = Util::mod(x, m_width);

    //setting tile like in setTile
    if(m_tiles[x][y]) delete m_tiles[x][y];
    m_tiles[x][y] = tile;

    if(update) updateTilesFrom(x, y);
    if(redraw) redrawTilesFrom(x, y);
    return true;
}
void World::breakTile(int x, int y, bool update, bool redraw)
{
    if(!inWorldRange(x, y)) return;
    x = Util::mod(x, m_width);

    if(m_tiles[x][y]) delete m_tiles[x][y];
    m_tiles[x][y] = nullptr;

    if(update) updateTilesFrom(x, y);
    if(redraw) redrawTilesFrom(x, y);
}
void World::redrawTilesFrom(int x, int y)
{
    //redrawing this tile and 8 neighbours (if on screen)
}
void World::updateTilesFrom(int x, int y)
{
    //updating 4 neighbour tiles to tile at x,y
}
bool World::inWorldRange(int x, int y)
{
    return (y >= 0 && y < m_height);
}
void World::drawFromLayerToScreen(ALLEGRO_BITMAP* layer)
{
    Util::drawBitmap(layer, 0, 0);
}
void World::listForegroundTileBorders(int x, int y) //this method may be able to be optimised.
{
    Tile* tile = getTile(x, y);
    std::vector<DrawableTileBorder> neighbours;
    for(int xx = -1; xx <= 1; ++xx)
    {
        for(int yy = -1; yy <= 1; ++ yy)
        {
            if(yy == 0 && xx == 0) continue;
            Tile* currentNeighbourTile = getTile(x + xx, y + yy);
            if(currentNeighbourTile == nullptr) continue;
            neighbours.push_back(DrawableTileBorder {currentNeighbourTile, currentNeighbourTile->spritesheetId(), x + xx, y + yy, tile, x, y});
        }
    }
    size_t numberOfEntries = neighbours.size();
    auto isDuplicatedLater = [&numberOfEntries, &neighbours] (int indexOfCurrent) -> bool
    {
        size_t index = indexOfCurrent + 1;
        if(neighbours[indexOfCurrent].tile)
        {
            int id = neighbours[indexOfCurrent].tile->id();
            for(; index < numberOfEntries; ++index)
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
            for(; index < numberOfEntries; ++index)
            {
                DrawableTileBorder& entry = neighbours[index];
                if(entry.tile == nullptr) return true;
            }
        }
        return false;
    };

    for(size_t i = 0; i < numberOfEntries; ++i)
    {
        if(isDuplicatedLater(i)) continue;
        m_foregroundBorderBuffer.push_back(neighbours[i]);
    }
}
void World::listForegroundTile(int x, int y)
{
    Tile* tile = getTile(x, y);
    if(!tile) return;
    m_foregroundTileBuffer.push_back(DrawableTile {tile, tile->spritesheetId(), x, y});
}
void World::drawForegroundTileBuffer()
{
    if(m_foregroundTileBuffer.empty()) return;
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();

    ALLEGRO_DISPLAY* currentDisplay = root.display();
    al_set_target_bitmap(m_foregroundTileLayer);
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
            al_draw_prim(toDraw.data(), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
            toDraw.clear();
            toDraw.reserve(10000);
            lastSpritesheetId = currentSpritesheetId;
        }
        tile.tile->drawInner(this, toDraw, tile.x, tile.y);
    }
    if(toDraw.size()) al_draw_prim(toDraw.data(), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    al_set_target_bitmap(al_get_backbuffer(currentDisplay));
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
void World::listMissingForegroundTilesToBuffer()
{
    Root& root = Root::instance();
    int windowWidth = root.windowWidth();
    int windowHeight = root.windowHeight();
    Vec2D worldCoordsTopLeft = screenToWorld(Vec2D(0.0, 0.0));
    Vec2D worldCoordsBottomRight = screenToWorld(Vec2D(windowWidth, windowHeight));
    int firstTileX = Util::fastFloor(worldCoordsTopLeft.x / 16.0f);
    int firstTileY = Util::fastFloor(worldCoordsTopLeft.y / 16.0f);

    int lastTileX = Util::fastFloor(worldCoordsBottomRight.x / 16.0f);
    int lastTileY = Util::fastFloor(worldCoordsBottomRight.y / 16.0f);

    int firstTileToExcludeX = Util::fastFloor(m_cameraAtLastRedraw.x / 16.0f);
    int firstTileToExcludeY = Util::fastFloor(m_cameraAtLastRedraw.y / 16.0f);

    int lastTileToExcludeX = Util::fastFloor((m_cameraAtLastRedraw.x + windowWidth) / 16.0f);
    int lastTileToExcludeY = Util::fastFloor((m_cameraAtLastRedraw.y + windowHeight) / 16.0f);

    Vec2D cameraDiff = Vec2D(m_cameraAtLastRedraw) - m_camera;

    if(cameraDiff.x > 0.0) lastTileToExcludeX += 1000; //we dont need to draw tiles on left side when we go right etc.
    if(cameraDiff.x < 0.0) firstTileToExcludeX -= 1000;
    if(cameraDiff.y > 0.0) lastTileToExcludeY += 1000;
    if(cameraDiff.y < 0.0) firstTileToExcludeY -= 1000;

    for(int x = firstTileX; x <= lastTileX; ++x) //checking every tile is needed if we want to check whether tile wants an updating draw.
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            // some ties are not necesserily drawn
            if(!(x <= firstTileToExcludeX || x >= lastTileToExcludeX || y <= firstTileToExcludeY || y >= lastTileToExcludeY))
            {
                y = lastTileToExcludeY - 1;
                continue;
            }
            listForegroundTile(x, y);
        }
    }
}
void World::listMissingForegroundBordersToBuffer()
{
    Root& root = Root::instance();
    int windowWidth = root.windowWidth();
    int windowHeight = root.windowHeight();
    Vec2D worldCoordsTopLeft = screenToWorld(Vec2D(0.0, 0.0));
    Vec2D worldCoordsBottomRight = screenToWorld(Vec2D(windowWidth, windowHeight));
    int firstTileX = Util::fastFloor(worldCoordsTopLeft.x / 16.0f);
    int firstTileY = Util::fastFloor(worldCoordsTopLeft.y / 16.0f);

    int lastTileX = Util::fastFloor(worldCoordsBottomRight.x / 16.0f);
    int lastTileY = Util::fastFloor(worldCoordsBottomRight.y / 16.0f);

    int firstTileToExcludeX = Util::fastFloor(m_cameraAtLastRedraw.x / 16.0f);
    int firstTileToExcludeY = Util::fastFloor(m_cameraAtLastRedraw.y / 16.0f);

    int lastTileToExcludeX = Util::fastFloor((m_cameraAtLastRedraw.x + windowWidth) / 16.0f);
    int lastTileToExcludeY = Util::fastFloor((m_cameraAtLastRedraw.y + windowHeight) / 16.0f);

    Vec2D cameraDiff = Vec2D(m_cameraAtLastRedraw) - m_camera;

    if(cameraDiff.x > -0.0) lastTileToExcludeX += 1000; //we dont need to draw tiles on left side when we go right etc.
    if(cameraDiff.x < 0.0) firstTileToExcludeX -= 1000;
    if(cameraDiff.y > -0.0) lastTileToExcludeY += 1000;
    if(cameraDiff.y < 0.0) firstTileToExcludeY -= 1000;

    for(int x = firstTileX; x <= lastTileX; ++x) //checking every tile is needed if we want to check whether tile wants an updating draw.
    {
        for(int y = firstTileY; y <= lastTileY; ++y)
        {
            // some ties are not necesserily drawn


            if(!(x <= firstTileToExcludeX || x >= lastTileToExcludeX || y <= firstTileToExcludeY || y >= lastTileToExcludeY))
            {
                y = lastTileToExcludeY - 1;
                continue;
            }

            if(y < -1 || y > m_height) continue; //border has to be drawn outside of world too

            listForegroundTileBorders(x, y);
        }
    }
}
void World::drawForegroundBorderBuffer()
{
    if(m_foregroundBorderBuffer.empty()) return;
    Root& root = Root::instance();
    SpritesheetDatabase* spritesheetDatabase = root.spritesheetDatabase();

    ALLEGRO_DISPLAY* currentDisplay = root.display();
    al_set_target_bitmap(m_foregroundBorderLayer);
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
            al_draw_prim(toDraw.data(), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
            toDraw.clear();
            toDraw.reserve(10000);
            lastSpritesheetId = currentSpritesheetId;
        }
        tile.tile->drawOuter(this, toDraw, tile.x, tile.y, tile.destX, tile.destY, tile.destTile);
    }
    if(toDraw.size()) al_draw_prim(toDraw.data(), NULL, spritesheetDatabase->getSpritesheetById(lastSpritesheetId), 0, toDraw.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    al_set_target_bitmap(al_get_backbuffer(currentDisplay));
    //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
void World::draw() //in every drawing function coordinates need to be floored, not casted to int
{
    Vec2I cam = Util::fastFloor(m_camera);

    int shiftX = m_cameraAtLastRedraw.x - cam.x;
    int shiftY = m_cameraAtLastRedraw.y - cam.y;


    if(shiftX || shiftY) //we want to draw missing tiles only when it is needed
    {
        m_foregroundTileBuffer.clear(); //this may be needed to be out due to redrawing tiles in other place.
        m_foregroundTileBuffer.reserve(10000); //need to be reserved better.

        m_foregroundBorderBuffer.clear();
        m_foregroundBorderBuffer.reserve(10000); //need to be reserved better.

        // drawing foreground tiles
        m_bitmapShifter->shift(m_foregroundTileLayer, shiftX, shiftY, al_map_rgba(0, 0, 0, 0));
        m_bitmapShifter->shift(m_foregroundBorderLayer, shiftX, shiftY, al_map_rgba(0, 0, 0, 0));

        listMissingForegroundTilesToBuffer();
        listMissingForegroundBordersToBuffer();

        drawForegroundTileBuffer();
        drawForegroundBorderBuffer();

        m_cameraAtLastRedraw.x -= shiftX;
        m_cameraAtLastRedraw.y -= shiftY;
    }

    //TODO: redrawing tiles that request it

    drawFromLayerToScreen(m_foregroundTileLayer);
    drawFromLayerToScreen(m_foregroundBorderLayer);
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
Vec2D World::screenToWorld(const Vec2D& screen)
{
    return screen + m_camera;
}
Vec2D World::worldToScreen(const Vec2D& world)
{
    return world - m_camera;
}
Vec2D World::camera() const
{
    return m_camera;
}
WorldGenerator* World::worldGenerator() const
{
    return m_worldGenerator;
}
void World::moveCamera(const Vec2D& diff)
{
    m_camera += diff;
    float xDiff = m_cameraAtLastRedraw.x - m_camera.x;
    float yDiff = m_cameraAtLastRedraw.y - m_camera.y;
    double rem = m_camera.x - Util::fastFloor(m_camera.x);
    m_camera.x = Util::mod(Util::fastFloor(m_camera.x), m_width * 16); //integer modulo
    m_camera.x += rem;
    if(abs(m_camera.x - (float)(int)m_camera.x) < 0.001) m_camera.x += 0.001; //drwaing seems to be wrong with close to integer camera posisitons. This seems to be helping. But reason is not known.
    if(abs(m_camera.y - (float)(int)m_camera.y) < 0.001) m_camera.y += 0.001;
    m_cameraAtLastRedraw.x = Util::fastFloor(m_camera.x + xDiff);
    m_cameraAtLastRedraw.y = Util::fastFloor(m_camera.y + yDiff);
}
float World::distance(const Vec2D& a, const Vec2D& b)
{
    float xDiff = b.x - a.x;
    if(abs(xDiff) > m_width * 16 / 2.0f) //point is closer in the other way
    {
        xDiff = m_width * 16 - xDiff;
    }
    float yDiff = b.y - a.y;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}
Vec2D World::way(const Vec2D& from, const Vec2D& to) //may need fix and there has to be a better name
{
    float xDiff = to.x - from.x;
    if(abs(xDiff) <= m_width * 16 / 2.0f)
    {
        return to - from;
    }
    if(to.x < from.x)
    {
        return to - from + Vec2D(m_width * 16, 0);
    }
    else
    {
        return to - from - Vec2D(m_width * 16, 0);
    }
}
