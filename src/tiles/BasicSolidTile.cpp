#include "BasicSolidTile.h"


BasicSolidTile::BasicSolidTile(Configuration& config, StaticTileData* staticTileData) :
    Tile(config, staticTileData)
{

}
BasicSolidTile::BasicSolidTile(const BasicSolidTile& other)
{
    m_staticTileData = other.m_staticTileData;
}
BasicSolidTile::~BasicSolidTile()
{

}

void BasicSolidTile::drawInner(World* world, std::vector<ALLEGRO_VERTEX>& toDraw, int x, int y)
{
    Vec2F screenCoords = world->worldToScreen(Vec2F(x * 16, y * 16));
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    /* triangle vertices are added clockwise. Top left and bottom right triangle. */
    /*                x                       y                       z  u              v              color */
    float textureX = 0.0f;
    float textureY = 0.0f;
    toDraw.push_back({screenCoords.x        , screenCoords.y        , 0, textureX     , textureY     , color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
    toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y + 16.0f, 0, textureX + 16, textureY + 16, color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
    toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});

    return;
}
void BasicSolidTile::drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& toDraw, int x, int y, int outX, int outY)
{

}
void BasicSolidTile::update(World* world, int x, int y)
{

}
void BasicSolidTile::randomUpdate(World* world, int x, int y)
{

}
void BasicSolidTile::constantUpdate(World* world, int x, int y)
{

}

Tile* BasicSolidTile::clone() const
{
    return new BasicSolidTile(*this);
}
Tile* BasicSolidTile::create(Configuration& config, StaticTileData* staticTileData) const
{
    return new BasicSolidTile(config, staticTileData);
}

StaticTileData* BasicSolidTile::createStaticTileData(Configuration& config, int id) const
{
    return new StaticData(config, id);
}
