#ifndef STATICTILEDATA_H
#define STATICTILEDATA_H

#include <string>
#include "../Configuration.h"

class StaticTileData
{
public:
    StaticTileData(Configuration& config, int id);
    virtual ~StaticTileData();

    int id() const;
    int spritesheetId() const;
    std::string name() const;
protected:
    int m_id;
    int m_spritesheetId;
    std::string m_name;
private:
};

#endif // STATICTILEDATA_H
