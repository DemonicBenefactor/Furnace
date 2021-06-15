

#include "ResourceManager.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "json.hpp"

///////////////////////Singleton Setup Start
ResourceManager *ResourceManager::instance = 0;
ResourceManager *ResourceManager::getInstance() {
  if (instance == 0) {
    instance = new ResourceManager();
  }
  return instance;
}
/////////////////////////Singleton Setup End

bool ResourceManager::loadTexture(std::string fileName, std::string id,
                                  SDL_Renderer *pRenderer) {
  SDL_Texture *pTexture = IMG_LoadTexture(pRenderer, fileName.c_str());
  if (pTexture != 0) {
    mTextureMap[id] = pTexture;
    return true;
  }
  throw std::runtime_error("failed to load " + fileName);
  return false;
}

void ResourceManager::drawTexture(std::string id, int x, int y, int width,
                                  int height, int currentRow, int currentFrame,
                                  SDL_Renderer *pRenderer,
                                  SDL_RendererFlip flip) {
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow - 1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, mTextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void ResourceManager::clearTexture(std::string id) { mTextureMap.erase(id); }

// JSON==========================================================================
void ResourceManager::loadJson(const std::string fileName,
                               const std::string stateID) {
  std::ifstream ifs(fileName);
  nlohmann::json jf = nlohmann::json::parse(ifs);
  for (auto &state : jf.items()) {
    if (state.key() == stateID) {
      for (auto &catagory : state.value().items()) {
        if (catagory.key() == "Textures") {
          std::cout << "TBD textures" << std::endl;
          for (auto &texture : catagory.value().items()) {
            std::cout << texture.key() << " : " << texture.value() << std::endl;
          }
        }
        if (catagory.key() == "Objects") {
          for (auto &object : catagory.value().items()) {
            std::cout << "create some objects" << std::endl;
          }
        }
      }
    }
  }
}

// GLTF==========================================================================
void ResourceManager::loadGLTF(const std::string fileName,
                               const std::string id) {
  tinygltf::Model model;
  // tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;
  bool ret = true;

  // bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, fileName.c_str());
  // bool ret = loader.LoadBinaryFromFile(&model, &err, &warn,
  // fileName.c_str()); // for binary glTF(.glb)

  if (!warn.empty()) {
    std::cout << "Warn: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cout << "Err: " << err << std::endl;
  }

  if (!ret) {
    std::cout << "Failed to parse glTF" << std::endl;
    return;
  }

  // mGLTF[id] = model;
}

void ResourceManager::clean() { mTextureMap.clear(); }
