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

		void setState(current_state state) 
				{ changeState = true; currentState = state; }
		void push(std::shared_ptr<GameState> state);
		void change(std::shared_ptr<GameState> state);
		void pop() { popState = true; }
    
private:		
		current_state currentState;
		bool changeState;
		bool popState;
        std::vector<std::shared_ptr<GameState>> gameStates;
};
//MENU STATE============================================================
class MenuState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return menuID;}

		
	private:
		static void buttonLocal();
		static void buttonOnline() {}
		static void buttonOptions() {}
		static void buttonExit();

		static const std::string menuID;
		std::vector<std::unique_ptr<SDLSceneNode>> sceneNodes;
};
//LOCAL STATE==============================================================
class LocalState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return localID;}
	private:
		static const std::string localID;
		std::vector<std::unique_ptr<SDLSceneNode>> sceneNodes;
};
//ONLINE STATE==============================================================
class OnlineState : public GameState
{
public:
	virtual void update() {}
	virtual void render() {}
	virtual bool onEnter() { return true; }
	virtual bool onExit() { return true; }
	virtual std::string getStateID() const { return onlineID; }
private:
	static const std::string onlineID;
	std::vector<std::unique_ptr<SDLSceneNode>> sceneNodes;
};
//OPTIONS STATE=============================================================
class OptionsState : public GameState
{
public:
	virtual void update() {}
	virtual void render() {}
	virtual bool onEnter() { return true; }
	virtual bool onExit() { return true; }
	virtual std::string getStateID() const { return optionsID; }
private:
	static const std::string optionsID;
	std::vector<std::unique_ptr<SDLSceneNode>> sceneNodes;
};
//PAUSE STATE================================================================
class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return pauseID; }
private:
	static void buttonResume();
	static void buttonMenu();

	
	static const std::string pauseID;
	std::vector<std::unique_ptr<SDLSceneNode>> sceneNodes;
};

#endif //__GameStateMachine__
