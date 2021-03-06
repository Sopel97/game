#include "Configuration.h"
#include "../LibS/Geometry.h"

using namespace Geo;

Configuration::Configuration(const std::string& path) :
    m_table(LuaTable::fromFile(path.c_str()))
{
}

Configuration::~Configuration()
{

}

ConfigurationNode Configuration::operator[](const std::string& nodePath)
{
    return m_table[nodePath.c_str()];
}

ConfigurationNode Configuration::operator[](int index)
{
    return m_table[index];
}
