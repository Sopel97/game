#ifndef TILEDATABASE_H
#define TILEDATABASE_H

#include <vector>
#include <map>
#include <string>

class Root;
class Assets;
class Tile;
class StaticTileData;

class TileDatabase
{
public:
    TileDatabase();
    virtual ~TileDatabase();

    void addBaseTile(Tile* tile, const std::string& name);
    Tile* getBaseTile(const std::string& name);

    Tile* getTileTemplateById(int id);
    Tile* getTileTemplateByName(const std::string& name);
    int getTileTemplateIdByName(const std::string& name);

    StaticTileData* getStaticTileDataByTileId(int id);
    StaticTileData* getStaticTileDataByTileName(const std::string& name);

    Tile* createNewTileById(int id);
    Tile* createNewTileByName(const std::string& name);

    void addTile(const std::string& path);
    void load(Assets* assets);

protected:
private:
    int m_lastId;

    std::vector<Tile*> m_tiles;
    std::map<std::string, int> m_tilesMap;

    std::map<std::string, Tile*> m_baseTiles; //base tiles don't have static tile data (they only define tile beahviour). They are only used to create proper tiles from configs. Static tile data is loaded from config when creating tile.

    std::vector<StaticTileData*> m_staticTileDatas;
};

#endif // TILEDATABASE_H
