#ifndef ROOT_H
#define ROOT_H

class Assets;
class SpritesheetDatabase;
class TileDatabase;
class World;
struct ALLEGRO_TIMER;

class Root
{
public:
    virtual ~Root();
    static Root& instance();

    Assets* assets() const;
    SpritesheetDatabase* spritesheetDatabase() const;
    TileDatabase* tileDatabase() const;

    World* world() const;

    void start();

protected:
private:
    Root();
    Assets* m_assets;
    SpritesheetDatabase* m_spritesheetDatabase;
    TileDatabase* m_tileDatabase;

    World* m_world;

    const int FPS = 120;
    bool fpsLimit;
    const int TPS = 60;
    int currentFps;
    int currentTps;

    ALLEGRO_TIMER* drawTimer;
    ALLEGRO_TIMER* tickTimer;
    unsigned long long int ticks;

    void addBaseTilesToDatabase();
};

#endif // ROOT_H
