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
int Tile::outerBorderPrecedence() const
{
    return m_staticTileData->outerBorderPrecedence();
}
bool Tile::hasInnerBorder() const
{
    return m_staticTileData->hasInnerBorder();
}
bool Tile::hasOuterBorder() const
{
    return m_staticTileData->hasOuterBorder();
}

int Tile::innerBorderType() const
{
    return m_staticTileData->innerBorderType();
}
Vec2F Tile::textureOffset() const
{
    return m_staticTileData->textureOffset();
}
