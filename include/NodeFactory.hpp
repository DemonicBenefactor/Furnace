#include <string>
#include <memory>
#include <map>
#include "NodeGraph.hpp"

class NodeCreator
{
    public:
        typedef std::shared_ptr<SceneNode> nodePtr;
        virtual nodePtr createSceneNode() const = 0;
        virtual ~NodeCreator() {}        
};

class NodeFactory
{
    private:
        //singlton
        NodeFactory() {}
        ~NodeFactory() {}
        static NodeFactory *instance;

    public:
        static NodeFactory *getInstance();

        typedef std::shared_ptr<SceneNode> nodePtr;
        typedef std::shared_ptr<NodeCreator> creatorPtr;
        bool registerType(std::string typeID, creatorPtr);
        nodePtr create(std::string typeID);
        
    private:
        std::map<std::string, creatorPtr> creators;
};
