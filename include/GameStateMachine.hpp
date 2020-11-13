#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <string>
#include <vector>

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

    private:
        std::vector<GameState*> m_gameStates;
};

class MenuState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return s_menuID;}
	private:
		static const std::string s_menuID;
};

class PlayState : public GameState
{
	public:
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
		virtual std::string getStateID() const {return s_playID;}
	private:
		static const std::string s_playID;
};

#endif //__GameStateMachine__
