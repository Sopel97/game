#ifndef ROOT_H
#define ROOT_H

class Assets;
class SpritesheetDatabase;

class Root
{
public:
    virtual ~Root();
    static Root& instance();

    Assets* assets() const;
    SpritesheetDatabase* spritesheetDatabase() const;

    void start();

protected:
private:
    Root();
    Assets* m_assets;
    SpritesheetDatabase* m_spritesheetDatabase;
};

#endif // ROOT_H
