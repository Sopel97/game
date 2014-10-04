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
#include "WorldGenerator.h"

#include "EmptyTile.h"
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

    if(al_is_system_installed()) //allegro deinitializes itself before global destructors are called. Without this check allegro crashes.
    {
        al_destroy_timer(m_drawTimer);
        al_destroy_timer(m_tickTimer);
    }
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
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    m_windowWidth = 1024;
    m_windowHeight = 768;
    m_display = al_create_display(m_windowWidth, m_windowHeight);
    m_drawTimer = al_create_timer(1.0 / FPS);
    m_tickTimer = al_create_timer(1.0 / TPS);
    m_fpsLimit = false;
    /* Initializing assets */
    m_assets = new Assets();

    /* Initializing spritesheets */
    m_spritesheetDatabase = new SpritesheetDatabase();
    m_spritesheetDatabase->load(m_assets);

    /* Initializing tiles */
    m_tileDatabase = new TileDatabase();
    addBaseTilesToDatabase();
    m_tileDatabase->load(m_assets);

    /* World generator */
    //temporarly it will be hardcoded world generator path/handle/id
    std::vector<std::string> generators = m_assets->worldGenerators();
    if(generators.empty())
    {
        std::cout << "No world generators found. Exiting.";
        return;
    }
    Configuration worldGeneratorConfig = Configuration(generators[0]);
    m_worldGenerator = new WorldGenerator(worldGeneratorConfig);

    /* Creating world */
    m_world = new World(m_worldGenerator);

    al_start_timer(m_tickTimer);
    al_start_timer(m_drawTimer);
    int framesThisSecond = 0;
    int ticksThisSecond = 0;
    int lastTicks = al_get_timer_count(m_tickTimer);
    int lastFPSTicks = al_get_timer_count(m_drawTimer);
    for(;;)
    {
        ALLEGRO_KEYBOARD_STATE currentKeyboardState;
        al_get_keyboard_state(&currentKeyboardState);
        int nowTicks = al_get_timer_count(m_tickTimer);
        int nowDrawTicks = al_get_timer_count(m_drawTimer);

        if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_ESCAPE))
        {
            return;
        }

        if(nowTicks != lastTicks && !(nowTicks % TPS))
        {
            m_currentFps = framesThisSecond;
            framesThisSecond = 0;
            m_currentTps = ticksThisSecond;
            ticksThisSecond = 0;

            std::cout << "FPS: " << m_currentFps << "\nTPS: " << m_currentTps << "\n\n";
        }

        if(nowTicks != lastTicks)
        {
            lastTicks = nowTicks;
            ++m_ticks;
            ++ticksThisSecond;

#define HIGH_SPEED_CAMERA

#ifndef HIGH_SPEED_CAMERA
            /* low camera speed */

            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_LEFT))
            {
                m_world->moveCamera(Vec2D(-3, 0));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_RIGHT))
            {
                m_world->moveCamera(Vec2D(3, 0));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_UP))
            {
                m_world->moveCamera(Vec2D(0, -3));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_DOWN))
            {
                m_world->moveCamera(Vec2D(0, 3));
            }
#else
            /* high camera speed */
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_LEFT))
            {
                m_world->moveCamera(Vec2F(-20.3, 0));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_RIGHT))
            {
                m_world->moveCamera(Vec2F(20.3, 0));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_UP))
            {
                m_world->moveCamera(Vec2F(0, -20.3));
            }
            if(al_key_down(&currentKeyboardState, ALLEGRO_KEY_DOWN))
            {
                m_world->moveCamera(Vec2F(0, 20.3));
            }

#endif // HIGH_SPEED_CAMERA
            m_world->update();
        }
        if(nowDrawTicks != lastFPSTicks || !m_fpsLimit)
        {
            lastFPSTicks = nowDrawTicks;
            ++framesThisSecond;
            al_clear_to_color(al_map_rgb(64, 128, 255));
            m_world->draw();
            al_flip_display();
        }
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
    m_tileDatabase->addBaseTile(new EmptyTile(), "EmptyTile");
}

int Root::windowWidth() const
{
    return m_windowWidth;
}
int Root::windowHeight() const
{
    return m_windowHeight;
}
WorldGenerator* Root::worldGenerator() const
{
    return m_worldGenerator;
}
ALLEGRO_DISPLAY* Root::display() const
{
    return m_display;
}
