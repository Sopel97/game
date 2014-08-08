#include "Assets.h"

Assets::Assets()
{

}

Assets::~Assets()
{

}

std::vector<std::string> Assets::graphicsAssets() const
{
    return scanForFiles("assets\\gfx\\", "*.png");
}

std::vector<std::string> Assets::tileAssets() const
{
    return scanForFiles("assets\\tiles\\", "*.tile");
}

std::vector<std::string> Assets::worldGenerators() const
{
    return scanForFiles("assets\\worldGenerators\\", "*.gen");
}

std::vector<std::string> Assets::scanForFiles(const std::string& path, const std::string& finds) const
{
    std::vector<std::string> files;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    std::string fullPath = path+finds;
    hFind = FindFirstFile(fullPath.c_str(), &findFileData);
    if(!(hFind == INVALID_HANDLE_VALUE))
    {
        files.push_back(path+findFileData.cFileName);
    }
    while(FindNextFile(hFind, &findFileData))
    {
        files.push_back(path+findFileData.cFileName);
    }
    FindClose(hFind);
    return files;
}
