#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <map>
#include "SDL2/SDL.h"

class TextureManager
{
private:
    //singleton
    TextureManager() {}
    ~TextureManager() {}
    static TextureManager *instance;

public:
    static TextureManager *getInstance();
    
    bool load(std::string fileName, std::string id, 
            SDL_Renderer *pRenderer);
    
    void draw(std::string id, int x, int y, 
            int width, int height, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void drawFrame(std::string id, int x, int y, 
            int width, int height, int currentRow,
            int currentFrame, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
    
private:
    
    std::map<std::string, SDL_Texture*> m_textureMap;
   
};

typedef TextureManager TheTextureManager;

#endif // __TextureManager__
