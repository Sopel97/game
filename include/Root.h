#ifndef ROOT_H
#define ROOT_H

class Assets;
class SpritesheetDatabase;
class TileDatabase;

class Root
{
public:
    virtual ~Root();
    static Root& instance();

    Assets* assets() const;
    SpritesheetDatabase* spritesheetDatabase() const;
    TileDatabase* tileDatabase() const;

    void start();

protected:
private:
    Root();
    Assets* m_assets;
    SpritesheetDatabase* m_spritesheetDatabase;
    TileDatabase* m_tileDatabase;
};

#endif // ROOT_H
