#include <iostream>
#include <vector>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "Root.h"
#include "Configuration.h"
#include "Assets.h"
#include "SpritesheetDatabase.h"
#include "TileDatabase.h"
#include "World.h"

#include "BasicSolidTile.h"

Root::Root()
{
}

Root::~Root()
{
    delete m_world;
    delete m_tileDatabase;
    delete m_spritesheetDatabase;
    delete m_assets;
    //deiniting allegro stuff
}

Root& Root::instance()
{
    static Root _instance;
    return _instance;
}

void Root::start()
{
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    al_create_display(1024, 768);
    drawTimer = al_create_timer(1.0 / FPS);
    tickTimer = al_create_timer(1.0 / TPS);
    fpsLimit = false;

    /* Initializing assets */
    m_assets = new Assets();

    /* Initializing spritesheets */
    m_spritesheetDatabase = new SpritesheetDatabase();
    m_spritesheetDatabase->load();

    /* Initializing tiles */
    m_tileDatabase = new TileDatabase();
    addBaseTilesToDatabase();
    m_tileDatabase->load();

    /* Creating world */
    m_world = new World(512, 128); //size is temporary

    al_start_timer(tickTimer);
    al_start_timer(drawTimer);
    int framesThisSecond = 0;
    int ticksThisSecond = 0;
    int lastTicks = al_get_timer_count(tickTimer);
    int lastFPSTicks = al_get_timer_count(drawTimer);
    for(;;)
    {
        ALLEGRO_KEYBOARD_STATE currentKeyboardState;
        al_get_keyboard_state(&currentKeyboardState);
        int nowTicks = al_get_timer_count(tickTimer);
        int nowDrawTicks = al_get_timer_count(drawTimer);

        if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_ESCAPE))
        {
            break;
        }
        if(nowTicks != lastTicks && !(nowTicks % TPS))
        {
            currentFps = framesThisSecond;
            framesThisSecond = 0;
            currentTps = ticksThisSecond;
            ticksThisSecond = 0;
            std::cout << "FPS: " << currentFps << "\nTPS: " << currentTps << "\n\n";
        }
        if(nowTicks != lastTicks)
        {
            lastTicks = nowTicks;
            ++ticks;
            ++ticksThisSecond;

            m_world->update();
        }
        if(nowDrawTicks != lastFPSTicks || !fpsLimit)
        {
            lastFPSTicks = nowDrawTicks;
            ++framesThisSecond;

            m_world->draw();
        }
        al_flip_display();
    }
}

Assets* Root::assets() const
{
    return m_assets;
}

SpritesheetDatabase* Root::spritesheetDatabase() const
{
    return m_spritesheetDatabase;
}
TileDatabase* Root::tileDatabase() const
{
    return m_tileDatabase;
}

World* Root::world() const
{
    return m_world;
}

void Root::addBaseTilesToDatabase()
{
    m_tileDatabase->addBaseTile(new BasicSolidTile(), "BasicSolidTile");
}
