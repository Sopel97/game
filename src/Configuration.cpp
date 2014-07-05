#include "Configuration.h"

Configuration::Configuration(const std::string path) :
    m_table(LuaTable::fromFile(path.c_str()))
{

}

Configuration::~Configuration()
{

}

LuaTableNode Configuration::operator[](const std::string nodePath)
{
    return m_table[nodePath.c_str()];
}
