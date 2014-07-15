#ifndef STATICTILEDATA_H
#define STATICTILEDATA_H

#include <string>
#include "../Configuration.h"

class StaticTileData
{
public:
    StaticTileData(Configuration& config, int id);
    virtual ~StaticTileData();

    virtual int id() const;
    virtual int spritesheetId() const;
    virtual std::string name() const;
    virtual int borderPrecedence() const;
    virtual bool hasInnerBorder() const;
    virtual bool hasOuterBorder() const;
protected:
    int m_id;
    int m_spritesheetId;
    std::string m_name;
    int m_borderPrecendence;
    bool m_hasInnerBorder;
    bool m_hasOuterBorder;
private:
};

#endif // STATICTILEDATA_H
