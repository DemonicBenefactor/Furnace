#ifndef __InputHandler__
#define __InputHandler__

#include <vector>
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "SDL2/SDL.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

enum controller_axis
{
    LEFT_STICK,
    RIGHT_STICK,
    TRIGGERS
};

enum pad_direction
{
    PAD_NONE = 0,
    PAD_UP = 1,
    PAD_UP_RIGHT = 2,
    PAD_RIGHT = 3,
    PAD_DOWN_RIGHT = 4,
    PAD_DOWN = 5,
    PAD_DOWN_LEFT = 6,
    PAD_LEFT = 7,
    PAD_UP_LEFT = 8,
    DEADZONE = 8000 
};


class InputHandler
{
    private:
        //singlton
        InputHandler();
        ~InputHandler();
        static InputHandler *instance;

    public:
        
        static InputHandler *getInstance();
        
        void update();

        //accessors
        bool        getKey(SDL_Scancode key);
        bool        getMouseButton(int button) const
                    {return m_mouseButtonStates[button];}
        
        glm::vec2   getMousePosition()
                    {return m_mousePosition;}       
        
        bool        joysticksInitialised() const 
                    {return m_bGamepadsInited;}
        
        glm::vec2   getPadAxis(int player, controller_axis axis);
        bool        getPadButton(int player, int which);
    
            
    private:
		
        std::vector<bool>   m_mouseButtonStates;
        glm::vec2           m_mousePosition;
        //mouse events
        void onMouseMove(SDL_Event &event);
        void onMouseButtonDown(SDL_Event &event);
        void onMouseButtonUp(SDL_Event &event);
        //joystick events
        void onAxisMove(SDL_Event &event);
        void onJoystickButtonDown(SDL_Event &event) {}
        void onJoystickButtonUp(SDL_Event &event) {}

        //joystick members
        std::vector<SDL_GameController*> m_gamepads;	
        bool                m_bGamepadsInited;
        //keyboard members
        const Uint8         *m_keystates; 
};

typedef InputHandler TheInputHandler;

#endif //__InputHandler__
