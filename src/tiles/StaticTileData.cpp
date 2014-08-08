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
    m_outerBorderPrecendence = config["outerBorderPrecedence"].getDefault<int>(0);
    m_innerBorderType = config["innerBorderType"].getDefault<int>(0);
    m_hasInnerBorder = config["hasInnerBorder"].getDefault<bool>(false);
    m_hasOuterBorder = config["hasOuterBorder"].getDefault<bool>(false);
    m_textureOffset.x = config["textureOffset"][1].getDefault<float>(0.0f);
    m_textureOffset.y = config["textureOffset"][2].getDefault<float>(0.0f);

}

StaticTileData::StaticTileData(const StaticTileData& data)
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

int StaticTileData::outerBorderPrecedence() const
{
    return m_outerBorderPrecendence;
}
bool StaticTileData::hasInnerBorder() const
{
    return m_hasInnerBorder;
}
bool StaticTileData::hasOuterBorder() const
{
    return m_hasOuterBorder;
}

int StaticTileData::innerBorderType() const
{
    return m_innerBorderType;
}
Vec2F StaticTileData::textureOffset() const
{
    return m_textureOffset;
}
