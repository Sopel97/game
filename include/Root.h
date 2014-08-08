#ifndef ROOT_H
#define ROOT_H

class Assets;
class SpritesheetDatabase;
class TileDatabase;
class World;
class WorldGenerator;

struct ALLEGRO_DISPLAY;
struct ALLEGRO_TIMER;

class Root
{
public:
    virtual ~Root();
    static Root& instance();

    Assets* assets() const;
    SpritesheetDatabase* spritesheetDatabase() const;
    TileDatabase* tileDatabase() const;

    WorldGenerator* worldGenerator() const;

    World* world() const;

    void start();

    ALLEGRO_DISPLAY* display() const;

    int windowWidth() const;
    int windowHeight() const;

protected:
private:
    Root();
    Root(const Root& root);
    Root(Root&& root);
    Assets* m_assets;
    SpritesheetDatabase* m_spritesheetDatabase;
    TileDatabase* m_tileDatabase;

    WorldGenerator* m_worldGenerator;

    World* m_world;

    ALLEGRO_DISPLAY* m_display;

    const int FPS = 60;
    const int TPS = 60;

    bool m_fpsLimit;
    int m_currentFps;
    int m_currentTps;

    int m_windowWidth;
    int m_windowHeight;

    ALLEGRO_TIMER* m_drawTimer;
    ALLEGRO_TIMER* m_tickTimer;
    unsigned long long int m_ticks;

    void addBaseTilesToDatabase();
};

#endif // ROOT_H
