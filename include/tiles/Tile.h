#ifndef TILE_H
#define TILE_H

#include <string>
#include "../../geometry/Geometry.h"
#include "../Configuration.h"
#include "StaticTileData.h"
using namespace Geo;
class Tile
{
public:
    Tile(Configuration& config, StaticTileData* staticTileData);
    Tile(const Tile& other);
    virtual ~Tile();
    virtual int id() const;
    virtual int spritesheetId() const;
    virtual std::string name() const;
    virtual Vec2I position() const;
    virtual StaticTileData* staticTileData() const;
    virtual void setPosition(const Vec2I& newPosition);

    virtual void draw() const = 0;
    virtual void update() const = 0;
    virtual void randomUpdate() const = 0;
    virtual void constantUpdate() const = 0;

    virtual Tile* clone() const = 0;
    virtual Tile* create(Configuration& config, StaticTileData* staticTileData) const = 0;

protected:
    StaticTileData* m_staticTileData;
    Vec2I m_position;
private:
};

#endif // TILE_H
