#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdlutils.h"
#include "sprite.h"
#include "planet.h"

#define INHIBIT(X) X
//~ #define INHIBIT(X) /* X */

#define APP_NAME "Tatanga"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Constants for sprite
#define GAP_SPRITE_GROUND           11
#define GAP_SPRITE_CENTER_GROUND    20
#define RUN_SPEED_MAX               6.0
#define RUN_ACCELERATION            0.1
#define RUN_DECELERATION            0.1
#define START_ANIM_IDLE             StartAnim(0, 6, 7)
#define START_ANIM_RUN              StartAnim(1, 8, 3)
#define START_ANIM_STRIKE           StartAnim(2, 2, 5)
#define START_ANIM_JUMP             StartAnim(3, 3, 8)

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern std::map<std::string, SDL_Texture*> g_textures;

class Planet;
extern std::vector<Planet*> g_planets;
