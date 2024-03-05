#ifndef __ResourceManager__
#define __ResourceManager__

// #define TINYGLTF_IMPLEMENTATION
// #define STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "NodeGraph.hpp"
#include "Gui.hpp"
#include "Player.hpp"
#include "tiny_gltf.h" //includes json.hpp
#include <fstream>

class ResourceManager {

public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = delete;
  ResourceManager& operator=(const ResourceManager &) = delete;
  ResourceManager& operator=(ResourceManager&&) = delete;
    
    static ResourceManager &Get() {
    static ResourceManager singleton;
    return singleton;
  }

  // SDL Texture ========================================
  bool loadTexture(const std::string fileName, const std::string id,
                   SDL_Renderer *pRenderer);

  void drawTexture(const std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer *pRenderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

  void clearTexture(std::string id);

  // XML  ===============================================

  void loadXML() {}

  // Json  ==============================================

  void loadJson(const std::string fileName, const std::string stateID,
          std::vector<std::unique_ptr<Node2D>> &sceneNodes);

  // GLTF ===============================================

  void loadGLTF(const std::string fileName, const std::string id);

  // Shader =============================================

  void loadShader() {}

  void clean();

private:
  ResourceManager() {} //singleton
  std::map<std::string, SDL_Texture *> mTextureMap;
  std::map<std::string, tinygltf::Model> mGLTF;
};

#endif // __ResourceManager__
