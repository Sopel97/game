#include "TileDatabase.h"
#include "Root.h"
#include "Assets.h"
#include "Tile.h"

TileDatabase::TileDatabase()
{
    m_lastId = 1;
    m_tiles.push_back(nullptr); //reserved for air tile
    m_tilesMap.insert(std::pair<std::string, int>("Air", 0));
}
TileDatabase::~TileDatabase()
{
    for(std::pair<std::string, Tile*> baseTile : m_baseTiles)
    {
        delete baseTile.second;
    }
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
Tile* TileDatabase::getTileTemplateById(int id)
{
    return m_tiles[id];
}
Tile* TileDatabase::getTileTemplateByName(const std::string& name)
{
    return m_tiles[m_tilesMap[name]];
}
int TileDatabase::getTileTemplateIdByName(const std::string& name)
{
    return m_tilesMap[name];
}

StaticTileData* TileDatabase::getStaticTileDataByTileId(int id)
{
    return getTileTemplateById(id)->staticTileData();
}
StaticTileData* TileDatabase::getStaticTileDataByTileName(const std::string& name)
{
    return getTileTemplateByName(name)->staticTileData();
}
void TileDatabase::addTile(const std::string& path)
{
    Configuration tileConfig(path);
    std::string baseTileName = tileConfig["baseTileName"].getDefault<std::string>("");
    std::string name = tileConfig["name"].getDefault<std::string>("");
    if(baseTileName == "" || baseTileName == "") return;

    Tile* baseTile = getBaseTile(baseTileName);

    StaticTileData* staticTileData = baseTile->createStaticTileData(tileConfig, m_lastId);
    m_tiles.push_back(baseTile->create(tileConfig, staticTileData));
    m_tilesMap.insert(std::pair<std::string, int>(name, m_lastId));

    std::cout << "  - " << path << '\n';

    ++m_lastId;
}
void TileDatabase::load(Assets* assets)
{
    int currentId = m_lastId;
    std::vector<std::string> tileAssets = assets->tileAssets();
    std::cout << "Found " << tileAssets.size() << " tiles:" << '\n';
    for(std::string& tileAsset : tileAssets)
    {
        addTile(tileAsset);
    }
    std::cout << "Loaded " << m_lastId - currentId << " tiles." << '\n' << '\n';
}
Tile* TileDatabase::createNewTileById(int id)
{
    Tile* tile = getTileTemplateById(id);
    if(tile) return tile->clone();

    return nullptr;
}
Tile* TileDatabase::createNewTileByName(const std::string& name)
{
    Tile* tile = getTileTemplateByName(name);
    if(tile) return tile->clone();

    return nullptr;
}
