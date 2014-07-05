#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <lua.h>
#include <string>

#include "../luatables/luatables.h"

class Configuration
{
public:
    Configuration(const std::string path);
    virtual ~Configuration();

    LuaTableNode operator[](const std::string nodePath);
protected:
    LuaTable m_table;
    std::string m_path;
private:
};

#endif // CONFIGURATION_H
