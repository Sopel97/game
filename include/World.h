#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "../geometry/Geometry.h"
#include "Util.h"
#include "Array2.h"
#include <allegro5/allegro_primitives.h>

using namespace Geo;
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
    Array2<Tile*> getTiles2(int x, int y, int tilesHorizontal, int tilesVertical);

    void setTile(Tile* tile, int x, int y);  //setting tile doesn't check if it's possible
    bool placeTile(Tile* tile, int x, int y);
    bool inWorldRange(int x, int y);

    void draw();
    void drawMissingForegroundTiles();
    void drawForegroundTileBuffer();
    void drawFromLayerToScreen(ALLEGRO_BITMAP* layer);
    void update();
    void doRandomTileUpdate();
    void doConstantTileUpdate();

    Vec2F screenToWorld(const Vec2F& screen);
    Vec2F worldToScreen(const Vec2F& world);
    Vec2F camera() const;

    void moveCamera(const Vec2F& diff);
    float distance(const Vec2F& a, const Vec2F& b); /* a.x and b.x must be in range <0, m_width> */
    Vec2F way(const Vec2F& from, const Vec2F& to); /* from.x and to.x must be in range <0, m_width> */
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
        int destX;
        int destY;
    };
    ALLEGRO_BITMAP* m_forgroundTileLayer;
    Util::BitmapShifter* m_bitmapShifter;
    int m_width; //this is world width in tiles. To get world width in pixels this value needs to be multiplied by 16
    int m_height;
    Array2<Tile*> m_tiles;

    Vec2F m_camera;
    Vec2F m_cameraAtLastRedraw;

    std::vector<DrawableTile> m_foregroundTileBuffer; //TODO: drawing functions (currently done only in drawMissingTiles) must put drawables to proper list and then they have to be drawn in main drawing function
};

#endif // WORLD_H
