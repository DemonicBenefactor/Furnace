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

InputHandler::InputHandler() : m_gamepads(0), m_keystates(nullptr), m_mousePosition{0,0}
{
    for (int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
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
                    m_gamepads.push_back(pad);
                }
                else 
                {
                    std::cout << SDL_GetError();
                }
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bGamepadsInited = true;
        std::cout << "Initialised " << 
            m_gamepads.size() << " gamepad/fightstick(s)" << std::endl;
    }
    else
    {
        m_bGamepadsInited = false;
    }
}

InputHandler::~InputHandler()
{
    for (unsigned int i=0; i < m_gamepads.size(); i++)
    {
        SDL_GameControllerClose(m_gamepads[i]);
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
                m_keystates = SDL_GetKeyboardState(0);
                break;
            case SDL_KEYUP:
                m_keystates = SDL_GetKeyboardState(0);
                break;
            default:
                break;
        }
    }
}


//======KEYBOARD STUFF=======================
bool InputHandler::getKey(SDL_Scancode key)
{
    if (m_keystates != 0 && m_keystates[key] == 1)
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
    if (m_gamepads.size() > 0)
        switch (axis)
        {
            case controller_axis::LEFT_STICK:
                return {SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_LEFTX), 
                       SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_LEFTY)};

            case controller_axis::RIGHT_STICK:
                return {SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_RIGHTX), 
                       SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_RIGHTY)};

            case controller_axis::TRIGGERS:
                return {SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_TRIGGERLEFT),
                       SDL_GameControllerGetAxis(m_gamepads[player], 
                                SDL_CONTROLLER_AXIS_TRIGGERRIGHT)};

            default:
                return glm::vec2{0,0};
        } 
        return glm::vec2{0,0};
}

bool        InputHandler::getPadButton(int player, SDL_GameControllerButton button)
{
    if (m_gamepads.size() > 0)
    {
        if (SDL_GameControllerGetButton(m_gamepads[player], button) == 1)
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
        m_mouseButtonStates[static_cast<int>(mouse_buttons::LEFT)] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[static_cast<int>(mouse_buttons::MIDDLE)] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[static_cast<int>(mouse_buttons::RIGHT)] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[static_cast<int>(mouse_buttons::LEFT)] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[static_cast<int>(mouse_buttons::MIDDLE)] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[static_cast<int>(mouse_buttons::RIGHT)] = false;
    }
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    m_mousePosition.x = static_cast<float>(event.motion.x);
    m_mousePosition.y = static_cast<float>(event.motion.y);
}
