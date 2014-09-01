#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <set>

#include "../geometry/Geometry.h"
#include "Util.h"
#include "Array2.h"
#include <allegro5/allegro_primitives.h>

class WorldGenerator;
class TileDatabase;

using namespace Geo;
class Tile;

class World
{
public:
    World(WorldGenerator* worldGenerator);
    virtual ~World();

    int width();
    int height();

    Tile* getTile(int x, int y);
    std::vector<Tile*> getTiles(int x, int y, int tilesHorizontal, int tilesVertical);
    Array2<Tile*> getTiles2(int x, int y, int tilesHorizontal, int tilesVertical);

    bool setTile(Tile* tile, int x, int y);  //setting tile doesn't check if it's possible
    bool placeTile(Tile* tile, int x, int y, bool update = true, bool redraw = true);
    bool createAndPlaceTileIfPossible(int id, int x, int y, bool update = true, bool redraw = true);
    bool createAndPlaceTileIfPossible(const std::string& name, int x, int y, bool update = true, bool redraw = true);
    bool createAndPlaceTileIfPossible(Tile* tile, int x, int y, bool update = true, bool redraw = true);

    void destroyTile(int x, int y, bool update = true, bool redraw = true);

    bool requestForegroundTileRedraw(int x, int y);

    bool inWorldRange(int x, int y); //checks only y coords

    void updateTilesFrom(int x, int y);
    void redrawTilesFrom(int x, int y);

    void performForegroundRedrawRequests();

    void draw();
    void listForegroundTile(int x, int y);
    void listMissingForegroundTilesToBuffer();
    void drawForegroundTileBuffer();

    void listForegroundBorders(int x, int y);
    void listMissingForegroundBordersToBuffer();
    void drawForegroundBorderBuffer();

    void drawFromLayerToScreen(ALLEGRO_BITMAP* layer);

    void update();
    void doRandomTileUpdate();
    void doConstantTileUpdate();

    Vec2D screenToWorld(const Vec2D& screen);
    Vec2D worldToScreen(const Vec2D& world);
    Vec2D camera() const;

    int fillTileId() const;

    WorldGenerator* worldGenerator() const;

    void moveCamera(const Vec2D& diff);
    double distance(const Vec2D& a, const Vec2D& b); /* a.x and b.x must be in range <0, m_width> */
    Vec2D way(const Vec2D& from, const Vec2D& to); /* from.x and to.x must be in range <0, m_width> */

    void adjustPosition(Vec2D& pos);
protected:
private:

    struct DrawableTile
    {
        Tile* tile;
        int spritesheetId;
        int x;
        int y;
    };

    struct DrawableTileBorder
    {
        Tile* tile;
        int spritesheetId;
        int x;
        int y;

        Tile* destTile;
        int destX;
        int destY;
    };
    Util::BitmapShifter* m_bitmapShifter;
    int m_width; //this is world width in tiles. To get world width in pixels this value needs to be multiplied by 16
    int m_height;
    Array2<Tile*> m_tiles;

    Vec2D m_camera;
    Vec2I m_cameraAtLastRedraw;

    int m_fillTileId;

    ALLEGRO_BITMAP* m_foregroundTileLayer;
    ALLEGRO_BITMAP* m_foregroundBorderLayer;

    std::vector<DrawableTile> m_foregroundTileBuffer;
    std::vector<DrawableTileBorder> m_foregroundBorderBuffer;

    std::vector<Vec2I> m_foregroundErasedTiles;
    std::vector<Vec2I> m_foregroundErasedBorders;

    class Vec2Icompare
    {
    public:
        bool operator()(const Vec2I& lhs, const Vec2I& rhs)
        {
            if(lhs.x < rhs.x) return true;
            else if (lhs.x == rhs.x) return lhs.y < rhs.y;
            return false;
        }
    };
    std::set<Vec2I, Vec2Icompare> m_foregroundRedrawRequests;

    WorldGenerator* m_worldGenerator;

    TileDatabase* m_tileDatabase;
};

#endif // WORLD_H
