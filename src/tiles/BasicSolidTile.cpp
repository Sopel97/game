#include "BasicSolidTile.h"


BasicSolidTile::BasicSolidTile(Configuration& config, StaticTileData* staticTileData) :
    Tile(config, staticTileData)
{

}
BasicSolidTile::BasicSolidTile(const BasicSolidTile& other)
{
    m_staticTileData = other.m_staticTileData;
}
BasicSolidTile::~BasicSolidTile()
{

}

void BasicSolidTile::draw(World* world, std::vector<ALLEGRO_VERTEX>& drawDefinition, int x, int y)
{
    std::cout << "draw\n";
}
void BasicSolidTile::drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& drawDefinition, int x, int y)
{
    std::cout << "draw outer\n";
}
void BasicSolidTile::update(World* world, int x, int y)
{
    std::cout << "update\n";
}
void BasicSolidTile::randomUpdate(World* world, int x, int y)
{

}
void BasicSolidTile::constantUpdate(World* world, int x, int y)
{

}

Tile* BasicSolidTile::clone() const
{
    return new BasicSolidTile(*this);
}
Tile* BasicSolidTile::create(Configuration& config, StaticTileData* staticTileData) const
{
    return new BasicSolidTile(config, staticTileData);
}

StaticTileData* BasicSolidTile::createStaticTileData(Configuration& config, int id) const
{
    return new StaticData(config, id);
}
