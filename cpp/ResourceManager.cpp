#include "ResourceManager.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


///////////////////////Singleton Setup Start
ResourceManager *ResourceManager::instance = 0;
ResourceManager *ResourceManager::getInstance()
{
    if (instance == 0)
    {
        instance = new ResourceManager();
    }
    return instance;
}
/////////////////////////Singleton Setup End

bool ResourceManager::loadTexture(std::string fileName, std::string id, 
            SDL_Renderer *pRenderer)
{
    SDL_Texture *pTexture = IMG_LoadTexture(pRenderer, fileName.c_str());
    if (pTexture != 0)
    {
        mTextureMap[id] = pTexture;
        return true;
    }
    return false;
}

void ResourceManager::drawTexture(std::string id, int x, int y, 
            int width, int height, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &srcRect,
            &destRect, 0, 0, flip);
}

void ResourceManager::drawTextureFrame(std::string id, int x, int y, 
            int width, int height, int currentRow,
            int currentFrame, SDL_Renderer *pRenderer,
            SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &srcRect,
            &destRect, 0, 0, flip);
}
