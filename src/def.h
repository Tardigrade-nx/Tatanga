#ifndef _DEF_H_
#define _DEF_H_

#include <list>
#include <map>
#include <string>
#include <SDL2/SDL.h>

//~ #define INHIBIT(X) X
#define INHIBIT(X) /* X */

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

// Switch button codes
#define SWITCH_KEY_A                   0
#define SWITCH_KEY_B                   1
#define SWITCH_KEY_X                   2
#define SWITCH_KEY_Y                   3
#define SWITCH_KEY_LSTICK              4
#define SWITCH_KEY_RSTICK              5
#define SWITCH_KEY_L                   6
#define SWITCH_KEY_R                   7
#define SWITCH_KEY_ZL                  8
#define SWITCH_KEY_ZR                  9
#define SWITCH_KEY_PLUS               10
#define SWITCH_KEY_MINUS              11
#define SWITCH_KEY_DLEFT              12
#define SWITCH_KEY_DUP                13
#define SWITCH_KEY_DRIGHT             14
#define SWITCH_KEY_DDOWN              15
#define SWITCH_KEY_LSTICK_LEFT        16
#define SWITCH_KEY_LSTICK_UP          17
#define SWITCH_KEY_LSTICK_RIGHT       18
#define SWITCH_KEY_LSTICK_DOWN        19
#define SWITCH_KEY_RSTICK_LEFT        20
#define SWITCH_KEY_RSTICK_UP          21
#define SWITCH_KEY_RSTICK_RIGHT       22
#define SWITCH_KEY_RSTICK_DOWN        23
#define SWITCH_KEY_SL_LEFT            24
#define SWITCH_KEY_SR_LEFT            25
#define SWITCH_KEY_SL_RIGHT           26
#define SWITCH_KEY_SR_RIGHT           27

// Button events for Switch
#define BUTTON_PRESSED_UP           event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_DUP || event.jbutton.button == SWITCH_KEY_LSTICK_UP)
#define BUTTON_PRESSED_RIGHT        event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_DRIGHT || event.jbutton.button == SWITCH_KEY_LSTICK_RIGHT)
#define BUTTON_PRESSED_DOWN         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_DDOWN || event.jbutton.button == SWITCH_KEY_LSTICK_DOWN)
#define BUTTON_PRESSED_LEFT         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_DLEFT || event.jbutton.button == SWITCH_KEY_LSTICK_LEFT)
#define BUTTON_PRESSED_JUMP         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_A || event.jbutton.button == SWITCH_KEY_B)
#define BUTTON_PRESSED_QUIT         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_PLUS)
#define BUTTON_PRESSED_NEXT         event.type == SDL_JOYBUTTONDOWN && (event.jbutton.button == SWITCH_KEY_MINUS)
#define BUTTON_HELD_UP              SDL_JoystickGetButton(g_joystick, SWITCH_KEY_DUP) || SDL_JoystickGetButton(g_joystick, SWITCH_KEY_LSTICK_UP)
#define BUTTON_HELD_RIGHT           SDL_JoystickGetButton(g_joystick, SWITCH_KEY_DRIGHT) || SDL_JoystickGetButton(g_joystick, SWITCH_KEY_LSTICK_RIGHT)
#define BUTTON_HELD_DOWN            SDL_JoystickGetButton(g_joystick, SWITCH_KEY_DDOWN) || SDL_JoystickGetButton(g_joystick, SWITCH_KEY_LSTICK_DOWN)
#define BUTTON_HELD_LEFT            SDL_JoystickGetButton(g_joystick, SWITCH_KEY_DLEFT) || SDL_JoystickGetButton(g_joystick, SWITCH_KEY_LSTICK_LEFT)

#else

// Button events for PC
#define BUTTON_PRESSED_UP           event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_UP
#define BUTTON_PRESSED_RIGHT        event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_RIGHT
#define BUTTON_PRESSED_DOWN         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_DOWN
#define BUTTON_PRESSED_LEFT         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_LEFT
#define BUTTON_PRESSED_JUMP         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_w
#define BUTTON_PRESSED_QUIT         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_ESCAPE
#define BUTTON_PRESSED_NEXT         event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_n
#define BUTTON_HELD_UP              SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]
#define BUTTON_HELD_RIGHT           SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]
#define BUTTON_HELD_DOWN            SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]
#define BUTTON_HELD_LEFT            SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]

#endif

#endif
