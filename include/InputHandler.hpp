#ifndef __InputHandler__
#define __InputHandler__

#include <vector>
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "SDL2/SDL.h"

const int DEADZONE = 8000;

enum class mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

enum class controller_axis
{
    LEFT_STICK,
    RIGHT_STICK,
    TRIGGERS
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
        bool        getMouseButton(mouse_buttons button) const
                    {return mouseButtonStates[static_cast<int>(button)];}
        
        glm::vec2   getMousePosition()
                    {return mousePosition;}       
        
        bool        joysticksInitialised() const 
                    {return gamepadsInited;}
        
        glm::vec2   getPadAxis(int player, controller_axis axis);
        bool        getPadButton(int player, SDL_GameControllerButton button);
    
            
    private:
		
        std::vector<bool>   mouseButtonStates;
        glm::vec2           mousePosition;
        //mouse events
        void onMouseMove(SDL_Event &event);
        void onMouseButtonDown(SDL_Event &event);
        void onMouseButtonUp(SDL_Event &event);
        //joystick events
        void onJoystickButtonDown(SDL_Event &event) {}
        void onJoystickButtonUp(SDL_Event &event) {}

        //joystick members
        std::vector<SDL_GameController*> gamepads;	
        bool                gamepadsInited;
        //keyboard members
        const Uint8         *keystates; 
};

typedef InputHandler TheInputHandler;

#endif //__InputHandler__
