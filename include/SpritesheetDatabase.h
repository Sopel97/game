#ifndef SPRITESHEETDATABASE_H
#define SPRITESHEETDATABASE_H

#include <vector>
#include <map>
#include <string>

class ALLEGRO_BITMAP;
class Assets;

class SpritesheetDatabase
{
public:
    SpritesheetDatabase();
    virtual ~SpritesheetDatabase();

    ALLEGRO_BITMAP* getSpritesheetById(const int id);
    ALLEGRO_BITMAP* getSpritesheetByName(const std::string& name);
    int getSpritesheetIdByName(const std::string& name);
    void addSpritesheet(const std::string& path);
    void load(Assets* assets);
protected:
private:
    int m_lastId;
    std::vector<ALLEGRO_BITMAP*> m_spritesheets;
    std::map<std::string, int> m_spritesheetsMap;
};

#endif // SPRITESHEETDATABASE_H
