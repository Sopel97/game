#ifndef ASSETS_H
#define ASSETS_H

#include <vector>
#include <string>
#include <windows.h>

class Assets
{
public:
    Assets();
    virtual ~Assets();

    //methods for getting assets of certain types
    std::vector<std::string> graphicsAssets() const;
protected:
private:
};
#endif // ASSETS_H
