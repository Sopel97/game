#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "Configuration.h"
#include "Util.h"
#include "Root.h"
#include "../geometry/Random.h"

#include <vector>
#include <map>

using namespace Random;

class World;
class Tile;

class WorldGenerator
{
public:
    class Layer
    {
    public:
        enum LayerParameter
        {
            NAME = 1,
            LOWER_BOUND_MIN = 2,
            LOWER_BOUND_MAX = 3,
            MAIN_TILE_NAME = 4,
            BOTTOM_OUTLINE_TILE_NAME = 5,
            BOTTOM_OVERFLOW = 6,
            BOTTOM_OVERFLOW_TILE_NAME = 7,
            NOISE_OCTAVES = 8,
            NOISE_PERSISTANCE = 9,
            NOISE_SCALE = 10
        };
        std::string name;
        Util::RangeF lowerBound;

        int mainTile;
        int bottomOutlineTile;

        int bottomOverflow;
        int bottomOverflowTile;

        //applies to lowerBound of layer
        int noiseOctaves;
        double noisePersistance;
        double noiseScale;
        Layer(ConfigurationNode layerNode);
        Layer();
    };

    WorldGenerator(Configuration& config);
    void generate(World* world);
    virtual ~WorldGenerator();

    Layer& getLayerById(int id);
    Layer& getLayerByName(const std::string& name);
    int getLayerIdByName(const std::string& name);

    void addLayer(const Layer& layer);

    int fillTile() const;

    int worldWidth() const;
    int worldHeight() const;
protected:
    int m_worldWidth;
    int m_worldHeight;
    int m_fillTile;
    Util::RangeF m_surfaceLevel;

    int m_lastLayerId;
    std::vector<Layer> m_layers;
    std::map<std::string, int> m_layersMap;

    int m_seed;

    XorshiftEngine m_randomEngine;
private:

};

#endif // WORLDGENERATOR_H
