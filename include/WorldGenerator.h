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
            name = layerNode[1].getDefault<std::string>("");
            lowerBound.min = layerNode[2].getDefault<float>(-1.0f);
            lowerBound.max = layerNode[3].getDefault<float>(-1.0f);
            std::string tileName;
            tileName = layerNode[4].getDefault<std::string>("Dirt");
            mainTile = tileDatabase->getTileByName(tileName);

            std::string bottomOutlineTileName = layerNode[5].getDefault<std::string>(tileName);
            bottomOutlineTile = tileDatabase->getTileByName(bottomOutlineTileName);

            bottomOverflow = layerNode[6].getDefault<int>(0);
            std::string bottomOverflowTileName = layerNode[7].getDefault<std::string>(bottomOutlineTileName);
            bottomOverflowTile = tileDatabase->getTileByName(bottomOutlineTileName);

            noiseOctaves = layerNode[8].getDefault<int>(5);
            noisePersistance = layerNode[9].getDefault<double>(1);
            noiseScale = layerNode[10].getDefault<double>(0.01);
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
