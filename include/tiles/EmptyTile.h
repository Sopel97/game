#ifndef EMPTYTILE_H_INCLUDED
#define EMPTYTILE_H_INCLUDED

#include <vector>

#include <allegro5/allegro_primitives.h>
#include "Tile.h"
#include "StaticTileData.h"

class EmptyTile : public Tile
{
public:
    class StaticData : public StaticTileData
    {
    public:
        StaticData(Configuration& config, int id) :
            StaticTileData(config, id)
        {
            m_hasInnerBorder = false;
            m_hasOuterBorder = false;
            m_innerBorderType = -1;
            m_outerBorderPrecendence = 0x7FFFFFFF;
        }
        virtual ~StaticData()
        {

        }
    protected:
    private:
    };

    EmptyTile() {}
    EmptyTile(Configuration& config, StaticTileData* staticTileData);
    EmptyTile(const EmptyTile& other);
    virtual ~EmptyTile();

    virtual void drawInner(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y);
    virtual void drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y, int outX, int outY, Tile* tileOut);
    virtual bool update(World* world, int x, int y);
    virtual void randomUpdate(World* world, int x, int y);
    virtual void constantUpdate(World* world, int x, int y);

    virtual Tile* clone() const;
    virtual Tile* create(Configuration& config, StaticTileData* staticTileData) const;

    virtual StaticTileData* createStaticTileData(Configuration& config, int id) const;

    virtual bool hasAnyData() const;

protected:
private:
};

#endif // EMPTYTILE_H_INCLUDED
