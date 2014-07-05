#include "Assets.h"

Assets::Assets()
{

}

Assets::~Assets()
{

}

std::vector<std::string> Assets::graphicsAssets() const
{
    std::vector<std::string> files;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    hFind = FindFirstFile("assets\\gfx\\*.png", &findFileData);
    if(!(hFind == INVALID_HANDLE_VALUE))
    {
        files.push_back(findFileData.cFileName);
    }
    while(FindNextFile(hFind, &findFileData))
    {
        files.push_back(findFileData.cFileName);
    }
    FindClose(hFind);
    return files;
}
