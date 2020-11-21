#ifndef __ResourceManager__
#define __ResourceManager__

#include <iostream>
#include <map>
#include "SDL2/SDL.h"

class ResourceManager
{
private:
    //singleton
    ResourceManager() {}
    ~ResourceManager() {}
    static ResourceManager *instance;

public:
    static ResourceManager *getInstance();
    
    bool loadTexture(std::string fileName, std::string id, 
            SDL_Renderer *pRenderer);
    
    void drawTexture(std::string id, int x, int y, 
            int width, int height, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void drawTextureFrame(std::string id, int x, int y, 
            int width, int height, int currentRow,
            int currentFrame, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    
private:
    
    std::map<std::string, SDL_Texture*> mTextureMap;
   
};

typedef ResourceManager TheResourceManager;

#endif // __ResourceManager__
