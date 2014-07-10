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

Root::Root()
{
}

Root::~Root()
{
    delete m_spritesheetDatabase;
    delete m_assets;
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
    al_create_display(1024, 768);

    /* Initializing assets */
    m_assets = new Assets();

    /* Initializing spritesheets */
    m_spritesheetDatabase = new SpritesheetDatabase();
    m_spritesheetDatabase->load();

    /* Initializing tiles */
    m_tileDatabase = new TileDatabase();
    m_tileDatabase->load();

    for(;;)
    {
        ALLEGRO_KEYBOARD_STATE keyboardState;
        al_get_keyboard_state(&keyboardState);
        if(al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
        {

            break;
        }
        al_draw_bitmap(m_spritesheetDatabase->getSpritesheetByName("dirt.png"), 32, 32, 0);
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
