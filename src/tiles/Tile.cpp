#include "Tile.h"


Tile::Tile(Configuration& config, StaticTileData* staticTileData) :
    m_staticTileData(staticTileData)
{

}
Tile::Tile(const Tile& other) :
    m_staticTileData(other.m_staticTileData)
{

}
Tile::~Tile()
{

}

int Tile::id() const
{
    return m_staticTileData->id();
}
StaticTileData* Tile::staticTileData() const
{
    return m_staticTileData;
}
int Tile::spritesheetId() const
{
    return m_staticTileData->spritesheetId();
}
std::string Tile::name() const
{
    return m_staticTileData->name();
}
