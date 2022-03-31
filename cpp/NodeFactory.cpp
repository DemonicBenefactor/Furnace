#include "NodeFactory.hpp"

///////////////////////Singleton Setup Start
NodeFactory *NodeFactory::instance = 0;
NodeFactory *NodeFactory::getInstance() {
  if (instance == 0) {
    instance = new NodeFactory();
  }
  return instance;
}
/////////////////////////Singleton Setup End

bool NodeFactory::registerType(std::string typeID, creatorPtr creator) {
  std::map<std::string, creatorPtr>::iterator it = creators.find(typeID);
  if (it != creators.end()) {
    return false;
  }

  creators[typeID] = creator;
  return true;
}

std::shared_ptr<SceneNode> NodeFactory::create(std::string typeID) {
  std::map<std::string, creatorPtr>::iterator it = creators.find(typeID);
  if (it == creators.end()) {
    std::cout << "could not find type: " << typeID << "\n";
    return 0;
  }
  creatorPtr creator = it->second;
  return creator->createSceneNode();
}
