#ifndef BASICSOLIDTILE_H
#define BASICSOLIDTILE_H

#include <vector>

#include <allegro5/allegro_primitives.h>
#include "Tile.h"
#include "StaticTileData.h"

class BasicSolidTile : public Tile
{
public:
    class StaticData : public StaticTileData
    {
    public:
        StaticData(Configuration& config, int id) :
            StaticTileData(config, id)
        {

        }
        virtual ~StaticData()
        {

        }
    protected:
    private:
    };

    BasicSolidTile() {}
    BasicSolidTile(Configuration& config, StaticTileData* staticTileData);
    BasicSolidTile(const BasicSolidTile& other);
    virtual ~BasicSolidTile();

    virtual void drawInner(World* world, std::vector<ALLEGRO_VERTEX>& toDraw, int x, int y);
    virtual void drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& toDraw, int x, int y, int outX, int outY, Tile* tileOut);
    virtual void update(World* world, int x, int y);
    virtual void randomUpdate(World* world, int x, int y);
    virtual void constantUpdate(World* world, int x, int y);

    virtual Tile* clone() const;
    virtual Tile* create(Configuration& config, StaticTileData* staticTileData) const;

    virtual StaticTileData* createStaticTileData(Configuration& config, int id) const;
protected:
private:
};

#endif // BASICSOLIDTILE_H
