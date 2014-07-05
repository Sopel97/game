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

Root::Root()
{
}

Root::~Root()
{

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
    al_create_display(1280, 1024);

    m_assets = new Assets();
    m_spritesheetDatabase = new SpritesheetDatabase();

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
