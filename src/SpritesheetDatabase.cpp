#include <iostream>
#include <vector>
#include <string>

#include "SpritesheetDatabase.h"
#include "Root.h"
#include "Assets.h"

SpritesheetDatabase::SpritesheetDatabase()
{
    m_lastId = 0;
}

SpritesheetDatabase::~SpritesheetDatabase()
{
    if(al_is_system_installed()) //allegro deinitializes itself before global destructors are called. Without this check allegro crashes.
    {
        for(ALLEGRO_BITMAP* bitmap : m_spritesheets)
        {
            al_destroy_bitmap(bitmap);
        }
    }
}
void SpritesheetDatabase::addSpritesheet(const std::string& path)
{
    std::string fileName = "assets\\gfx\\" + path;
    ALLEGRO_BITMAP* spritesheet = al_load_bitmap(fileName.c_str());
    m_spritesheets.push_back(spritesheet);
    m_spritesheetsMap.insert(std::pair<std::string, int>(path, m_lastId));
    std::cout << "  - Loaded " << path << '\n';

    ++m_lastId;
}
void SpritesheetDatabase::load()
{
    Root& root = Root::instance();
    std::vector<std::string> gfxAssets = root.assets()->graphicsAssets();
    std::cout << "Found " << gfxAssets.size() << " spritesheets:" << '\n';
    for(std::string& gfxAsset : gfxAssets)
    {
        addSpritesheet(gfxAsset);
    }
    std::cout << "Loaded " << gfxAssets.size() << " spritesheets." << '\n' << '\n';
}
ALLEGRO_BITMAP* SpritesheetDatabase::getSpritesheetById(const int id)
{
    return m_spritesheets[id];
}
ALLEGRO_BITMAP* SpritesheetDatabase::getSpritesheetByName(const std::string& name)
{
    return m_spritesheets[m_spritesheetsMap[name]];
}
int SpritesheetDatabase::getSpritesheetIdByName(const std::string& name)
{
    return m_spritesheetsMap[name];
}
