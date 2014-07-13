#include <string>

#include "StaticTileData.h"
#include "Root.h"
#include "SpritesheetDatabase.h"


StaticTileData::StaticTileData(Configuration& config, int id) :
    m_id(id)
{
    Root& root = Root::instance();
    std::string spritesheetName = config["spritesheet"].getDefault<std::string>("empty.png");
    m_spritesheetId = root.spritesheetDatabase()->getSpritesheetIdByName(spritesheetName);
    m_name = config["name"].getDefault<std::string>("No Name");
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
