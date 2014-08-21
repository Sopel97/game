#include "WorldGenerator.h"

#include "World.h"
#include "Tile.h"
#include "TileDatabase.h"
#include "../geometry/Noise.h"

#include <iostream>

using namespace Noise;

WorldGenerator::Layer::Layer()
{

}
WorldGenerator::Layer::Layer(LuaTableNode layerNode) //maybe replace LuaTableNode with smth like ConfigurationNode
{
    Root& root = Root::instance();
    TileDatabase* tileDatabase = root.tileDatabase();
    name = layerNode[LayerParameter::NAME].getDefault<std::string>("");
    lowerBound.min = layerNode[LayerParameter::LOWER_BOUND_MIN].getDefault<float>(-1.0f);
    lowerBound.max = layerNode[LayerParameter::LOWER_BOUND_MAX].getDefault<float>(-1.0f);
    std::string mainTileName = layerNode[LayerParameter::MAIN_TILE_NAME].getDefault<std::string>("Dirt");
    mainTile = tileDatabase->getTileTemplateByName(mainTileName);

    std::string bottomOutlineTileName = layerNode[LayerParameter::BOTTOM_OUTLINE_TILE_NAME].getDefault<std::string>(mainTileName);
    bottomOutlineTile = tileDatabase->getTileTemplateByName(bottomOutlineTileName);

    bottomOverflow = layerNode[LayerParameter::BOTTOM_OVERFLOW].getDefault<int>(0);
    std::string bottomOverflowTileName = layerNode[LayerParameter::BOTTOM_OVERFLOW_TILE_NAME].getDefault<std::string>(bottomOutlineTileName);
    bottomOverflowTile = tileDatabase->getTileTemplateByName(bottomOutlineTileName);

    noiseOctaves = layerNode[LayerParameter::NOISE_OCTAVES].getDefault<int>(5);
    noisePersistance = layerNode[LayerParameter::NOISE_PERSISTANCE].getDefault<double>(1);
    noiseScale = layerNode[LayerParameter::NOISE_SCALE].getDefault<double>(0.01);
}
WorldGenerator::WorldGenerator(Configuration& config)
{
    m_lastLayerId = 0;
    m_seed = 133; //temp
    m_worldWidth = config["width"].getDefault<int>(1);
    m_worldHeight = config["height"].getDefault<int>(1);
    m_surfaceLevel.min = config["surface"][1].getDefault<float>(0.0f);
    m_surfaceLevel.max = config["surface"][2].getDefault<float>(0.0f);

    LuaTableNode layers = config["layers"];
    int size = layers.length();
    for(int i = 1; i <= size; ++i)
    {
        Layer layer = Layer(layers[i]);
        if(layer.lowerBound.min < 0.0f) layer.lowerBound.min = m_worldHeight - 1;
        if(layer.lowerBound.max < 0.0f) layer.lowerBound.max = m_worldHeight - 1;
        addLayer(layer);
    }

    m_randomEngine = XorshiftEngine(m_seed);
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
    std::vector<std::vector<int>> layers;
    layers.reserve(m_worldWidth);
    layers.resize(m_worldWidth);
    SimplexNoiseD noise;
    int numberOfLayers = m_layers.size(); //+ surface
    for(int x = 0; x < m_worldWidth; ++x)
    {
        for(int i = 0; i < numberOfLayers; ++i)
        {
            double lowerBound = m_layers[i].lowerBound.min;
            double upperBound = m_layers[i].lowerBound.max;

            layers[x].push_back(noise.periodicSeededRangedOctaveNoise1(x, m_seed * i * 4313513, m_layers[i].noiseOctaves, m_layers[i].noisePersistance, m_layers[i].noiseScale, lowerBound, upperBound, m_worldWidth));
        }
    }

    for(int x = 0; x < m_worldWidth; ++x)
    {
        int layer = 0;
        for(int y = 0; y < m_worldHeight; ++y)
        {
            while(layer < numberOfLayers && y > layers[x][layer]) ++layer;

            if(layer >= numberOfLayers) break;
            Tile* tile = m_layers[layer].mainTile;
            if(y == layers[x][layer])
            {
                tile = m_layers[layer].bottomOutlineTile;
            }
            if(layer > 0)
            {
                Layer& previousLayer = m_layers[layer - 1];
                int overflow = previousLayer.bottomOverflow;
                int diff = overflow + layers[x][layer - 1] - y;
                if(diff > 0)
                {
                    float fraction = (float)diff / (float)overflow;
                    float r = m_randomEngine.nextFloat();
                    if(r < fraction)
                    {
                        tile = previousLayer.bottomOverflowTile;
                    }
                }
            }
            if(!tile)
            {
                continue;
            }
            Tile* tileClone = tile->clone();
            if(!(world->setTile(tileClone, x, y)))
            {
                delete tileClone;
            }
        }
    }
}

WorldGenerator::Layer& WorldGenerator::getLayerById(int id)
{
    return m_layers[id];
}
WorldGenerator::Layer& WorldGenerator::getLayerByName(const std::string& name)
{
    return m_layers[m_layersMap[name]];
}
int WorldGenerator::getLayerIdByName(const std::string& name)
{
    return m_layersMap[name];
}

void WorldGenerator::addLayer(const WorldGenerator::Layer& layer)
{
    m_layers.push_back(layer);
    m_layersMap.insert(std::pair<std::string, int>(layer.name, m_lastLayerId));
    ++m_lastLayerId;
}
