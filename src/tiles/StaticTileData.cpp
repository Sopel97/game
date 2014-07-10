#include "StaticTileData.h"

StaticTileData::StaticTileData(Configuration& config, int id) :
    m_id(id)
{

}

StaticTileData::~StaticTileData()
{

}

int StaticTileData::id() const
{
    return m_id;
}
int StaticTileData::spritesheetId() const
{
    return m_spritesheetId;
}
std::string StaticTileData::name() const
{
    return m_name;
}
