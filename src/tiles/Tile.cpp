#include "Tile.h"


Tile::Tile(Configuration& config, StaticTileData* staticTileData) :
    m_staticTileData(staticTileData),
    m_position(0,0)
{

}
Tile::Tile(const Tile& other) :
    m_staticTileData(other.m_staticTileData),
    m_position(other.m_position)
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
Vec2I Tile::position() const
{
    return m_position;
}
void Tile::setPosition(const Vec2I& newPosition)
{
    m_position = newPosition;
}
