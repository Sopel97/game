#include "TileDatabase.h"
#include "Root.h"
#include "Assets.h"
#include "Tile.h"

TileDatabase::TileDatabase()
{
    m_lastId = 1;
    m_tiles.push_back(nullptr); //reserved for air tile
    m_tilesMap.insert(std::pair<std::string, int>("null", 0));
}
TileDatabase::~TileDatabase()
{
    for(Tile* tile : m_tiles)
    {
        delete tile;
    }
    for(StaticTileData* staticTileData : m_staticTileDatas)
    {
        delete staticTileData;
    }
}
void TileDatabase::addBaseTile(Tile* tile, const std::string& name)
{
    m_baseTiles.insert(std::pair<std::string, Tile*>(name, tile));
}
Tile* TileDatabase::getBaseTile(const std::string& name)
{
    return m_baseTiles[name];
}
Tile* TileDatabase::getTileById(int id)
{
    return m_tiles[id];
}
Tile* TileDatabase::getTileByName(const std::string& name)
{
    return m_tiles[m_tilesMap[name]];
}
int TileDatabase::getTileIdByName(const std::string& name)
{
    return m_tilesMap[name];
}

StaticTileData* TileDatabase::getStaticTileDataByTileId(int id)
{
    return getTileById(id)->staticTileData();
}
StaticTileData* TileDatabase::getStaticTileDataByTileName(const std::string& name)
{
    return getTileByName(name)->staticTileData();
}
void TileDatabase::addTile(const std::string& path)
{
    std::string fileName = "assets\\tiles\\" + path;

    Configuration tileConfig(fileName);
    std::string baseTileName = tileConfig["baseTileName"].getDefault<std::string>("");
    std::string name = tileConfig["name"].getDefault<std::string>("");
    if(baseTileName == "" || baseTileName == "") return;

    Tile* baseTile = getBaseTile(baseTileName);

    StaticTileData* staticTileData = baseTile->createStaticTileData(tileConfig, m_lastId);

    m_tiles.push_back(baseTile->create(tileConfig, staticTileData));
    m_tilesMap.insert(std::pair<std::string, int>(name, m_lastId));

    std::cout << "  - Loaded " << path << '\n';

    ++m_lastId;
}
void TileDatabase::load()
{
    int currentId = m_lastId;
    Root& root = Root::instance();
    std::vector<std::string> tileAssets = root.assets()->tileAssets();
    std::cout << "Found " << tileAssets.size() << " tiles:" << '\n';
    for(std::string& tileAsset : tileAssets)
    {
        addTile(tileAsset);
    }
    std::cout << "Loaded " << m_lastId - currentId << " tiles." << '\n' << '\n';
}
