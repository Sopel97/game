#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "Configuration.h"

class World;

class WorldGenerator
{
public:
    WorldGenerator(Configuration& config);
    void generate(World* world);
    virtual ~WorldGenerator();

    int worldWidth() const;
    int worldHeight() const;
protected:
    int m_worldWidth;
    int m_worldHeight;
private:

};

#endif // WORLDGENERATOR_H
