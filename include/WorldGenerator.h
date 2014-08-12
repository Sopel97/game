#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "Configuration.h"
#include "Util.h"
#include "Root.h"
#include "TileDatabase.h"

#include <vector>
#include <map>

class World;

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

        Tile* mainTile;
        Tile* bottomOutlineTile;

        int bottomOverflow;
        Tile* bottomOverflowTile;

        //applies to lowerBound of layer
        int noiseOctaves;
        double noisePersistance;
        double noiseScale;
        Layer(LuaTableNode layerNode)
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
        Layer()
        {

        }
    };

    WorldGenerator(Configuration& config);
    void generate(World* world);
    virtual ~WorldGenerator();

    Layer& getLayerById(int id);
    Layer& getLayerByName(const std::string& name);
    int getLayerIdByName(const std::string& name);

    void addLayer(const Layer& layer);

    int worldWidth() const;
    int worldHeight() const;
protected:
    int m_worldWidth;
    int m_worldHeight;
    Util::RangeF m_surfaceLevel;

    int m_lastLayerId;
    std::vector<Layer> m_layers;
    std::map<std::string, int> m_layersMap;

    int m_seed;


private:

};

#endif // WORLDGENERATOR_H
