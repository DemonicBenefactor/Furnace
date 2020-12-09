#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <string>
#include <vector>
#include <memory>
#include "NodeGraph.hpp"

enum class current_state
{
	MENU,
	LOCAL,
	ONLINE,
	OPTIONS,
	PAUSE,
	GAMEOVER
};

class GameState //abstract class with pure virtual functions
{
	public:
		virtual void update() = 0;
		virtual void render() = 0;
		virtual bool onEnter() = 0;
		virtual bool onExit() = 0;
		virtual std::string getStateID() const = 0;
};
//========================================================================
class GameStateMachine
{    
public:
		void update();
		void render();
		void clean();

		void setState(current_state s) 
				{ mChangeState = true; mCurrentState = s; }
		void push(GameState* pState);
		void change(GameState* pState);
		void pop();
    
private:		
		current_state mCurrentState;
		bool mChangeState;
        std::vector<GameState*> mGameStates;
};
//=========================================================================
class MenuState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return sMenuID;}

		
	private:
		static void sButtonLocal();
		static void sButtonOnline() {}
		static void sButtonOptions() {}
		static void sButtonExit();

		static const std::string sMenuID;
		std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};
//=========================================================================
class LocalState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return sLocalID;}
	private:
		static const std::string sLocalID;
		std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};

#endif //__GameStateMachine__
