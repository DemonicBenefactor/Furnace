#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <string>
#include <vector>
#include <memory>
#include "NodeGraph.hpp"

class GameState //abstract class with pure virtual functions
{
	public:
		virtual void update() = 0;
		virtual void render() = 0;
		virtual bool onEnter() = 0;
		virtual bool onExit() = 0;
		virtual std::string getStateID() const = 0;
};

class GameStateMachine
{
    public:
        void pushState(GameState *pState);
        void changeState(GameState *pState);
        void popState();

		void update();
		void render();

    private:
        std::vector<GameState*> mGameStates;
};

class MenuState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return sMenuID;}
	private:
		static const std::string sMenuID;
		std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};

class PlayState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return sPlayID;}
	private:
		static const std::string sPlayID;
		std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};

#endif //__GameStateMachine__
