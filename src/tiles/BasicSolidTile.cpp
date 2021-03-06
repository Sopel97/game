#include "BasicSolidTile.h"

#include "../LibS/AllegroUtil.h"

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

void BasicSolidTile::drawInner(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y)
{
    Vec2F posOnScreen = Util::fastFloor(world->worldToScreen(Vec2D(x * 16.0, y * 16.0)));
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


        vertexData.push_back({posOnScreen.x       , posOnScreen.y       , 0, textureX    , textureY    , color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner top right
        posOnScreen.x += 8.0f;
        textureX = 8.0f;
        textureY = 32.0f;
        unsigned char topRight = (inner(precedences[2][0]) << 2) | (inner(precedences[1][0]) << 1) | (inner(precedences[2][1]));
        if(topRight == 4) textureY += 32.0f;
        else textureY += (topRight & 3) * 8.0f;

        vertexData.push_back({posOnScreen.x       , posOnScreen.y       , 0, textureX    , textureY    , color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner bottom left
        posOnScreen.x -= 8.0f;
        posOnScreen.y += 8.0f;
        textureX = 16.0f;
        textureY = 32.0f;
        unsigned char bottomLeft = (inner(precedences[0][2]) << 2) | (inner(precedences[1][2]) << 1) | (inner(precedences[0][1]));
        if(bottomLeft == 4) textureY += 32.0f;
        else textureY += (bottomLeft & 3) * 8.0f;

        vertexData.push_back({posOnScreen.x       , posOnScreen.y       , 0, textureX    , textureY    , color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});

        // inner bottom right
        posOnScreen.x += 8.0f;
        textureX = 24.0f;
        textureY = 32.0f;
        unsigned char bottomRight = (inner(precedences[2][2]) << 2) | (inner(precedences[1][2]) << 1) | (inner(precedences[2][1]));
        if(bottomRight == 4) textureY += 32.0f;
        else textureY += (bottomRight & 3) * 8.0f;

        vertexData.push_back({posOnScreen.x       , posOnScreen.y       , 0, textureX    , textureY    , color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y + 8.0f, 0, textureX + 8, textureY + 8, color});
        vertexData.push_back({posOnScreen.x + 8.0f, posOnScreen.y       , 0, textureX + 8, textureY    , color});
        vertexData.push_back({posOnScreen.x       , posOnScreen.y + 8.0f, 0, textureX    , textureY + 8, color});
    }
    else
    {
        //drawing solid center?
    }
    */

    Vec2F offset = textureOffset();
    Vec2F uv(0.0f + offset.x, 0.0f + offset.y);
    //float textureX = 0.0f + offset.x;
    //float textureY = 0.0f + offset.y;
    AllegroUtil::appendQuadAsTriangleList(vertexData, posOnScreen, posOnScreen + Vec2F(16.0f, 16.0f), uv, color);
    return;
}
void BasicSolidTile::drawOuter(World* world, std::vector<ALLEGRO_VERTEX>& vertexData, int x, int y, int outX, int outY, Tile* tileOut)
{
    if(!hasOuterBorder()) return;
    if(tileOut)
    {
        if(tileOut->outerBorderPrecedence() <= outerBorderPrecedence()) return;
    }
    int currentTileId = id();
    int currentTilePrecedence = outerBorderPrecedence();

    Vec2F posOnScreen = Util::fastFloor(world->worldToScreen(Vec2D(outX * 16.0, outY * 16.0)));
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    Array2<Tile*> neighbours;
    Array2<int> ids(3, 3);
    Array2<int> precedences(3, 3);
    neighbours = world->getTiles2(outX - 1, outY - 1, 3, 3);
    for(int x = 0; x < 3; ++x)
    {
        for(int y = 0; y < 3; ++y)
        {
            Tile* currentTile = neighbours[x][y];
            if(!currentTile)
            {
                ids[x][y] = 0; //air has highest precedence
                precedences[x][y] = 0;
            }
            else
            {
                ids[x][y] = currentTile->id();
                precedences[x][y] = currentTile->outerBorderPrecedence();
            }
        }
    }
    auto shouldDraw = [&currentTileId](int id) -> bool
    {
        return currentTileId == id;
    };
    auto biggerPrecedence = [&currentTilePrecedence](int id) -> bool
    {
        return currentTilePrecedence > id;
    };
    //float textureX;
    //float textureY;
    Vec2F offset = textureOffset();

    unsigned int spriteOffset1 = shouldDraw(ids[0][1]) | (shouldDraw(ids[1][0]) << 1) | (shouldDraw(ids[2][1]) << 2) | (shouldDraw(ids[1][2]) << 3);
    Vec2F uv(spriteOffset1 * 16.0f + offset.x, 0.0f + offset.y);
    //textureX = spriteOffset1 * 16.0f + offset.x;
    //textureY = 0.0f + offset.y;
    if(spriteOffset1)
    {
        AllegroUtil::appendQuadAsTriangleList(vertexData, posOnScreen, posOnScreen + Vec2F(16.0f, 16.0f), uv, color);
    }
    unsigned int p = biggerPrecedence(ids[0][1]) | (biggerPrecedence(ids[1][0]) << 1) | (biggerPrecedence(ids[2][1]) << 2) | (biggerPrecedence(ids[1][2]) << 3); //similar to spriteOffset1 but with precedences

    unsigned int spriteOffset2 = (shouldDraw(ids[0][0]) && !(p & 3)) | ((shouldDraw(ids[2][0]) && !(p & 6)) << 1) | ((shouldDraw(ids[2][2]) && !(p & 12)) << 2) | ((shouldDraw(ids[0][2]) && !(p & 9)) << 3) ;
    uv = Vec2F(spriteOffset2 * 16.0f + offset.x, 16.0f + offset.y);
    //textureX = spriteOffset2 * 16.0f + offset.x;
    //textureY = 16.0f + offset.y;
    if(spriteOffset2)
    {
        AllegroUtil::appendQuadAsTriangleList(vertexData, posOnScreen, posOnScreen + Vec2F(16.0f, 16.0f), uv, color);
    }
}
bool BasicSolidTile::update(World* world, int x, int y)
{
    return false;
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
bool BasicSolidTile::hasAnyData() const
{
    return false;
}
