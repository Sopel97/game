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
    Vec2I screenCoords = Util::fastFloor(world->worldToScreen(Vec2D(x * 16.0, y * 16.0)));
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
    /* we dont do inner borders anymore
    Array2<Tile*> neighbours;
    Array2<int> precedences(3, 3);
    neighbours = world->getTiles2(x - 1, y - 1, 3, 3);
    for(int x = 0; x < 3; ++x)
    {
        for(int y = 0; y < 3; ++y)
        {
            Tile* currentTile = neighbours[x][y];
            if(!currentTile) precedences[x][y] = -1;
            else if(!currentTile->hasInnerBorder()) precedences[x][y] = 0;
            else precedences[x][y] = currentTile->borderPrecedence();
        }
    }
    int currentTilePrecedence = precedences[1][1];
    float textureX = 0.0f;
    float textureY = 0.0f;
    auto inner = [&currentTilePrecedence] (int p) -> bool {return (p < 0 && p != currentTilePrecedence); };
    if(hasInnerBorder())
    {
        // inner top left
        textureX = 0.0f;
        textureY = 32.0f;
        unsigned char topLeft = (inner(precedences[0][0]) << 2) | (inner(precedences[1][0]) << 1) | (inner(precedences[0][1]));
        if(topLeft == 4) textureY += 32.0f;
        else textureY += (topLeft & 3) * 8.0f;


        toDraw.push_back({screenCoords.x       , screenCoords.y       , 0, textureX    , textureY    , color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner top right
        screenCoords.x += 8.0f;
        textureX = 8.0f;
        textureY = 32.0f;
        unsigned char topRight = (inner(precedences[2][0]) << 2) | (inner(precedences[1][0]) << 1) | (inner(precedences[2][1]));
        if(topRight == 4) textureY += 32.0f;
        else textureY += (topRight & 3) * 8.0f;

        toDraw.push_back({screenCoords.x       , screenCoords.y       , 0, textureX    , textureY    , color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner bottom left
        screenCoords.x -= 8.0f;
        screenCoords.y += 8.0f;
        textureX = 16.0f;
        textureY = 32.0f;
        unsigned char bottomLeft = (inner(precedences[0][2]) << 2) | (inner(precedences[1][2]) << 1) | (inner(precedences[0][1]));
        if(bottomLeft == 4) textureY += 32.0f;
        else textureY += (bottomLeft & 3) * 8.0f;

        toDraw.push_back({screenCoords.x       , screenCoords.y       , 0, textureX    , textureY    , color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner bottom right
        screenCoords.x += 8.0f;
        textureX = 24.0f;
        textureY = 32.0f;
        unsigned char bottomRight = (inner(precedences[2][2]) << 2) | (inner(precedences[1][2]) << 1) | (inner(precedences[2][1]));
        if(bottomRight == 4) textureY += 32.0f;
        else textureY += (bottomRight & 3) * 8.0f;

        toDraw.push_back({screenCoords.x       , screenCoords.y       , 0, textureX    , textureY    , color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        toDraw.push_back({screenCoords.x + 8.0f, screenCoords.y       , 0, textureX + 8, textureY    , color});
        toDraw.push_back({screenCoords.x       , screenCoords.y + 8.0f, 0, textureX    , textureY + 8, color});
    }
    else
    {
        //drawing solid center?
    }
    */

    Vec2F offset = textureOffset();
    float textureX = 0.0f + offset.x;
    float textureY = 0.0f + offset.y;
    toDraw.push_back({screenCoords.x        , screenCoords.y        , 0, textureX     , textureY     , color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
    toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y + 16.0f, 0, textureX + 16, textureY + 16, color});
    toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
    toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
    return;
}
void BasicSolidTile::drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& toDraw, int x, int y, int outX, int outY, Tile* tileOut)
{
    if(!hasOuterBorder()) return;
    if(tileOut)
    {
        if(tileOut->outerBorderPrecedence() <= outerBorderPrecedence()) return;
    }
    int currentTileId = id();
    Vec2I screenCoords = Util::fastFloor(world->worldToScreen(Vec2D(outX * 16.0, outY * 16.0)));
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    Array2<Tile*> neighbours;
    Array2<int> ids(3, 3);
    neighbours = world->getTiles2(outX - 1, outY - 1, 3, 3);
    for(int x = 0; x < 3; ++x)
    {
        for(int y = 0; y < 3; ++y)
        {
            Tile* currentTile = neighbours[x][y];
            if(!currentTile) ids[x][y] = 0; //air has highest precedence
            else ids[x][y] = currentTile->id();
        }
    }
    auto shouldDraw = [&currentTileId](int id) -> bool
    {
        return currentTileId == id;
    };
    float textureX;
    float textureY;
    Vec2F offset = textureOffset();
    unsigned int spriteOffset1 = shouldDraw(ids[0][1]) | (shouldDraw(ids[1][0]) << 1) | (shouldDraw(ids[2][1]) << 2) | (shouldDraw(ids[1][2]) << 3);
    textureX = spriteOffset1 * 16.0f + offset.x;
    textureY = 0.0f + offset.y;
    if(spriteOffset1)
    {
        toDraw.push_back({screenCoords.x        , screenCoords.y        , 0, textureX     , textureY     , color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
        toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y + 16.0f, 0, textureX + 16, textureY + 16, color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
        toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
    }

    unsigned int spriteOffset2 = (shouldDraw(ids[0][0]) && !(spriteOffset1 & 3)) | ((shouldDraw(ids[2][0]) && !(spriteOffset1 & 6)) << 1) | ((shouldDraw(ids[2][2]) && !(spriteOffset1 & 12)) << 2) | ((shouldDraw(ids[0][2]) && !(spriteOffset1 & 9)) << 3) ;
    textureX = spriteOffset2 * 16.0f + offset.x;
    textureY = 16.0f + offset.y;
    if(spriteOffset2)
    {
        toDraw.push_back({screenCoords.x        , screenCoords.y        , 0, textureX     , textureY     , color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
        toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y + 16.0f, 0, textureX + 16, textureY + 16, color});
        toDraw.push_back({screenCoords.x + 16.0f, screenCoords.y        , 0, textureX + 16, textureY     , color});
        toDraw.push_back({screenCoords.x        , screenCoords.y + 16.0f, 0, textureX     , textureY + 16, color});
    }
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
