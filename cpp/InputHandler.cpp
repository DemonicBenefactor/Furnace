#include <iostream>
#include "InputHandler.hpp"
#include "Game.hpp"


//===========================================
InputHandler *InputHandler::instance = 0;
InputHandler *InputHandler::getInstance()
{
    if (instance == 0)
    {
        instance = new InputHandler();
    }
    return instance;
}
//===========================================

InputHandler::InputHandler() : mGamepads(0), mKeystates(nullptr), mMousePosition{0,0}
{
    for (int i = 0; i < 3; i++)
    {
        mMouseButtonStates.push_back(false);
    }
    
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0 )
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            if (SDL_IsGameController(i))
            {
                SDL_GameController *pad = nullptr;
                pad = SDL_GameControllerOpen(i);
                if (pad != nullptr)
                {
                    mGamepads.push_back(pad);
                }
                else 
                {
                    std::cout << SDL_GetError();
                }
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        mGamepadsInited = true;
        std::cout << "Initialised " << 
            mGamepads.size() << " gamepad/fightstick(s)" << std::endl;
    }
    else
    {
        mGamepadsInited = false;
    }
}

InputHandler::~InputHandler()
{
    for (unsigned int i=0; i < mGamepads.size(); i++)
    {
        SDL_GameControllerClose(mGamepads[i]);
    }
}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                TheGame::getInstance()->quit();
                break;
            case SDL_JOYAXISMOTION:
                break;
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(event);
                break;
            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(event);
                break;
            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
            case SDL_KEYDOWN:
                mKeystates = SDL_GetKeyboardState(0);
                break;
            case SDL_KEYUP:
                mKeystates = SDL_GetKeyboardState(0);
                break;
            default:
                break;
        }
    }
}


//======KEYBOARD STUFF=======================
bool InputHandler::getKey(SDL_Scancode key)
{
    if (mKeystates != 0 && mKeystates[key] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//==========JOYSTICK STUFF===================   
glm::vec2   InputHandler::getPadAxis(int player, controller_axis axis)
{
    if (mGamepads.size() > 0)
        switch (axis)
        {
            case controller_axis::LEFT_STICK:
                return {SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_LEFTX), 
                       SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_LEFTY)};

            case controller_axis::RIGHT_STICK:
                return {SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_RIGHTX), 
                       SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_RIGHTY)};

            case controller_axis::TRIGGERS:
                return {SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_TRIGGERLEFT),
                       SDL_GameControllerGetAxis(mGamepads[player], 
                                SDL_CONTROLLER_AXIS_TRIGGERRIGHT)};

            default:
                return glm::vec2{0,0};
        } 
        return glm::vec2{0,0};
}

bool        InputHandler::getPadButton(int player, SDL_GameControllerButton button)
{
    if (mGamepads.size() > 0)
    {
        if (SDL_GameControllerGetButton(mGamepads[player], button) == 1)
        return true;
    }
    else 
    {
        return false;
    }
    return false;
}
//==============MOUSE STUFF=====================
void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::LEFT)] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::MIDDLE)] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::RIGHT)] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::LEFT)] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::MIDDLE)] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        mMouseButtonStates[static_cast<int>(mouse_buttons::RIGHT)] = false;
    }
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    mMousePosition.x = static_cast<float>(event.motion.x);
    mMousePosition.y = static_cast<float>(event.motion.y);
}
