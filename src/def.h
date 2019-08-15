#ifndef _DEF_H_
#define _DEF_H_

#include <vector>
#include <map>
#include <SDL2/SDL.h>

#define INHIBIT(X) X
//~ #define INHIBIT(X) /* X */

#define APP_NAME "Tatanga"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern std::map<std::string, SDL_Texture*> g_textures;

// Planets
class Planet;
extern std::vector<Planet*> g_planets;

// Cherries
class Sprite;
extern std::vector<Sprite*> g_cherries;

#endif
