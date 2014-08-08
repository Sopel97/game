#ifndef STATICTILEDATA_H
#define STATICTILEDATA_H

#include <string>
#include "../Configuration.h"
#include "../../geometry/Geometry.h"

using namespace Geo;
class StaticTileData
{
public:
    StaticTileData(Configuration& config, int id);
    StaticTileData(const StaticTileData& data);
    virtual ~StaticTileData();

    virtual int id() const;
    virtual int spritesheetId() const;
    virtual std::string name() const;
    virtual int outerBorderPrecedence() const;
    virtual int innerBorderType() const;
    virtual Vec2F textureOffset() const;
    virtual bool hasInnerBorder() const;
    virtual bool hasOuterBorder() const;
protected:
    int m_id;
    int m_spritesheetId;
    Vec2F m_textureOffset;
    std::string m_name;
    int m_outerBorderPrecendence;
    int m_innerBorderType; //two tiles with the same inner border type will not be separated
    bool m_hasInnerBorder;
    bool m_hasOuterBorder;

private:
};

#endif // STATICTILEDATA_H
