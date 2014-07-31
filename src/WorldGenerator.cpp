#include "WorldGenerator.h"

#include "World.h"

WorldGenerator::WorldGenerator(Configuration& config)
{
   m_worldWidth = config["width"].getDefault<int>(1);
   m_worldHeight = config["height"].getDefault<int>(1);
}

WorldGenerator::~WorldGenerator()
{

}

int WorldGenerator::worldWidth() const
{
    return m_worldWidth;
}
int WorldGenerator::worldHeight() const
{
    return m_worldHeight;
}
void WorldGenerator::generate(World* world)
{
    //generation
}
