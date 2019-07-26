#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdlutils.h"
#include "sprite.h"
#include "planet.h"

#define APP_NAME "Tatanga"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Constants for sprite animation
#define RUN_SPEED_MAX      5.0
#define RUN_ACCELERATION   0.1
#define RUN_DECELERATION   0.1
#define START_ANIM_IDLE    if (m_animId != 0) StartAnim(0, 6, 7)
#define START_ANIM_RUN     if (m_animId != 1) StartAnim(1, 8, 3)

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
