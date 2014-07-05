#include <iostream>
#include <vector>
#include <string>

#include "SpritesheetDatabase.h"
#include "Root.h"
#include "Assets.h"

SpritesheetDatabase::SpritesheetDatabase()
{
    Root& root = Root::instance();
    std::vector<std::string> gfxAssets = root.assets()->graphicsAssets();
    std::cout << "Found " << gfxAssets.size() << " spritesheets:" << '\n';
    int currentId = 0;
    for(std::string& gfxAsset : gfxAssets)
    {
        std::cout << " - " << gfxAsset << '\n';

        std::string fileName = "assets\\gfx\\" + gfxAsset;
        m_spritesheets.push_back(al_load_bitmap(fileName.c_str()));
        m_spritesheetsMap.insert(std::pair<std::string, int>(gfxAsset, currentId));

        ++currentId;
    }
    std::cout << "Loaded " << currentId << " of " << gfxAssets.size() << " spritesheets." << '\n' << '\n';

}

SpritesheetDatabase::~SpritesheetDatabase()
{

}

ALLEGRO_BITMAP* SpritesheetDatabase::getSpritesheetById(const int id)
{
    return m_spritesheets[id];
}
ALLEGRO_BITMAP* SpritesheetDatabase::getSpritesheetByName(const std::string name)
{
    return m_spritesheets[m_spritesheetsMap[name]];
}
int SpritesheetDatabase::getSpritesheetIdByName(const std::string name)
{
    return m_spritesheetsMap[name];
}
