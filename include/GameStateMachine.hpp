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
				{ mChangeState = true; mCurrentState = state; }
		void push(std::shared_ptr<GameState> pState);
		void change(std::shared_ptr<GameState> pState);
		void pop() { mPopState = true; }
    
private:		
		current_state mCurrentState;
		bool mChangeState;
		bool mPopState;
        std::vector<std::shared_ptr<GameState>> mGameStates;
};
//MENU STATE============================================================
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
//LOCAL STATE==============================================================
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
//ONLINE STATE==============================================================
class OnlineState : public GameState
{
public:
	virtual void update() {}
	virtual void render() {}
	virtual bool onEnter() { return true; }
	virtual bool onExit() { return true; }
	virtual std::string getStateID() const { return sOnlineID; }
private:
	static const std::string sOnlineID;
	std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};
//OPTIONS STATE=============================================================
class OptionsState : public GameState
{
public:
	virtual void update() {}
	virtual void render() {}
	virtual bool onEnter() { return true; }
	virtual bool onExit() { return true; }
	virtual std::string getStateID() const { return sOptionsID; }
private:
	static const std::string sOptionsID;
	std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};
//PAUSE STATE================================================================
class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return sPauseID; }
private:
	static void sButtonResume();
	static void sButtonMenu();
	
	static const std::string sPauseID;
	std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};

#endif //__GameStateMachine__
