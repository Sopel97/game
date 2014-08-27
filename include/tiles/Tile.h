#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include <allegro5/allegro_primitives.h>
#include "../../geometry/Geometry.h"
#include "World.h"
#include "../Configuration.h"
#include "StaticTileData.h"

using namespace Geo;
class Tile
{
public:
    Tile() {}
    Tile(Configuration& config, StaticTileData* staticTileData);
    Tile(const Tile& other);
    virtual ~Tile();
    virtual int id() const;
    virtual int spritesheetId() const;
    virtual std::string name() const;
    virtual StaticTileData* staticTileData() const;
    virtual int outerBorderPrecedence() const;
    virtual bool hasInnerBorder() const;
    virtual bool hasOuterBorder() const;
    virtual int innerBorderType() const;
    virtual Vec2F textureOffset() const;

    virtual void drawInner(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y) = 0;
    virtual void drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y, int outX, int outY, Tile* tileOut) = 0;

    virtual bool update(World* world, int x, int y) = 0;
    virtual void randomUpdate(World* world, int x, int y) = 0;
    virtual void constantUpdate(World* world, int x, int y) = 0;

    virtual Tile* clone() const = 0;
    virtual Tile* create(Configuration& config, StaticTileData* staticTileData) const = 0;

    virtual StaticTileData* createStaticTileData(Configuration& config, int id) const = 0;

protected:
    StaticTileData* m_staticTileData;
private:
};

#endif // TILE_H
