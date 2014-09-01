#include "EmptyTile.h"

EmptyTile::EmptyTile(Configuration& config, StaticTileData* staticTileData) :
    Tile(config, staticTileData)
{
}
EmptyTile::EmptyTile(const EmptyTile& other)
{
    m_staticTileData = other.m_staticTileData;
}
EmptyTile::~EmptyTile()
{

}

void EmptyTile::drawInner(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y)
{
    return;
}
void EmptyTile::drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y, int outX, int outY, Tile* tileOut)
{

}
bool EmptyTile::update(World* world, int x, int y)
{
    return false;
}
void EmptyTile::randomUpdate(World* world, int x, int y)
{

}
void EmptyTile::constantUpdate(World* world, int x, int y)
{

}

Tile* EmptyTile::clone() const
{
    return new EmptyTile(*this);
}
Tile* EmptyTile::create(Configuration& config, StaticTileData* staticTileData) const
{
    return new EmptyTile(config, staticTileData);
}
StaticTileData* EmptyTile::createStaticTileData(Configuration& config, int id) const
{
    return new StaticData(config, id);
}
bool EmptyTile::hasAnyData() const
{
    return false;
}
