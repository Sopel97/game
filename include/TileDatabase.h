#ifndef TILEDATABASE_H
#define TILEDATABASE_H

#include <vector>
#include <map>
#include "../luatables/luatables.h"
#include "Root.h"
#include "Assets.h"
#include "Tile.h"
class TileDatabase
{
public:
    TileDatabase();
    virtual ~TileDatabase();

    void addBaseTile(Tile* tile, const std::string& name);
    Tile* getBaseTile(const std::string& name);

    Tile* getTileById(int id);
    Tile* getTileByName(const std::string& name);
    int getTileIdByName(const std::string& name);

    StaticTileData* getStaticTileDataByTileId(int id);
    StaticTileData* getStaticTileDataByTileName(const std::string& name);

    void addTile(const std::string& path);
    void load();

protected:
private:
    int m_lastId;

    std::vector<Tile*> m_tiles;
    std::map<std::string, int> m_tilesMap;

    std::map<std::string, Tile*> m_baseTiles; //base tiles don't have static tile data. They are only used to create proper tiles from configs. Static tile data is loaded from config when creating tile.

    std::vector<StaticTileData*> m_staticTileDatas;
};

#endif // TILEDATABASE_H
