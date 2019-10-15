#ifndef _DEF_H_
#define _DEF_H_

#include <list>
#include <map>
#include <string>
#include <SDL2/SDL.h>

#define INHIBIT(X) X
//~ #define INHIBIT(X) /* X */

#define APP_NAME "Tatanga"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#ifdef __SWITCH__
#define PATH_PREFIX "romfs:/"
#else
#define PATH_PREFIX "res/"
#endif

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Joystick* g_joystick;
extern std::map<std::string, SDL_Texture*> g_textures;

// Planets
class Planet;
extern std::list<Planet*> g_planets;

// Cherries
class Sprite;
extern std::list<Sprite*> g_cherries;

#ifdef __SWITCH__

// Button events for Switch
//
// Switch               SDL
// A                    SDL_CONTROLLER_BUTTON_A
// B                    SDL_CONTROLLER_BUTTON_B
// X                    SDL_CONTROLLER_BUTTON_X
// Y                    SDL_CONTROLLER_BUTTON_Y
// d-pad up             SDL_CONTROLLER_BUTTON_DPAD_LEFT
// d-pad right          SDL_CONTROLLER_BUTTON_DPAD_RIGHT
// d-pad down           SDL_CONTROLLER_BUTTON_MAX
// d-pad left           SDL_CONTROLLER_BUTTON_DPAD_DOWN
// L                    SDL_CONTROLLER_BUTTON_START
// R                    SDL_CONTROLLER_BUTTON_LEFTSTICK
// ZL                   SDL_CONTROLLER_BUTTON_RIGHTSTICK
// ZR                   SDL_CONTROLLER_BUTTON_LEFTSHOULDER
// right stick click    SDL_CONTROLLER_BUTTON_GUIDE
// left stick click     ?
#define BUTTON_PRESSED_UP           event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define BUTTON_PRESSED_RIGHT        event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define BUTTON_PRESSED_DOWN         event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == SDL_CONTROLLER_BUTTON_MAX
#define BUTTON_PRESSED_LEFT         event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define BUTTON_PRESSED_JUMP         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SDL_CONTROLLER_BUTTON_A || event.jbutton.button == SDL_CONTROLLER_BUTTON_B)
#define BUTTON_HELD_UP              SDL_JoystickGetButton(g_joystick, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
#define BUTTON_HELD_RIGHT           SDL_JoystickGetButton(g_joystick, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
#define BUTTON_HELD_DOWN            SDL_JoystickGetButton(g_joystick, SDL_CONTROLLER_BUTTON_MAX)
#define BUTTON_HELD_LEFT            SDL_JoystickGetButton(g_joystick, SDL_CONTROLLER_BUTTON_DPAD_DOWN)

#else

// Button events for PC
#define BUTTON_PRESSED_UP           event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_UP
#define BUTTON_PRESSED_RIGHT        event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_RIGHT
#define BUTTON_PRESSED_DOWN         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_DOWN
#define BUTTON_PRESSED_LEFT         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_LEFT
#define BUTTON_PRESSED_JUMP         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_w
#define BUTTON_HELD_UP              SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]
#define BUTTON_HELD_RIGHT           SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]
#define BUTTON_HELD_DOWN            SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]
#define BUTTON_HELD_LEFT            SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]

#endif

#endif
