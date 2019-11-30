#include <iostream>
#include <SDL2/SDL_image.h>
#include "sdlutils.h"
#include "def.h"
#ifdef __SWITCH__
#include "switch.h"
#endif

//------------------------------------------------------------------------------

// Init SDL
bool SDLUtils::Init()
{
   INHIBIT(std::cout << "SDLUtils::Init()" << std::endl;)

   // Initialize romfs
   #ifdef __SWITCH__
   romfsInit();
   #endif

   // Initialize SDL
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
   {
      std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      return false;
   }

   // Intialize SDL_image
   int flags = IMG_INIT_PNG;
   if ((IMG_Init(flags) & flags) != flags)
   {
      std::cerr << "SDL_image could not initialize! IMG_GetError: " << IMG_GetError() << std::endl;
      return false;
   }

   // Initialize joystick
   INHIBIT(std::cout << "SDL_NumJoysticks: '" << SDL_NumJoysticks() << "'" << std::endl;)
   if (SDL_NumJoysticks() >= 1)
   {
      g_joystick = SDL_JoystickOpen(0);
      if (g_joystick == NULL)
      {
         std::cerr << "Unable to open joystick." << std::endl;
         return false;
      }
      INHIBIT(std::cout << "SDL_JoystickOpen OK" << std::endl;)
   }

   // Create window
   #ifdef __SWITCH__
   g_window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
   #else
   g_window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   #endif
   if (g_window == NULL)
   {
      std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      return false;
   }

   // Create renderer
   g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (g_renderer == NULL)
   {
      std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      return false;
   }

   // Set draw color
   SDL_SetRenderDrawColor(g_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
   return true;
}

//------------------------------------------------------------------------------

// Close SDL
void SDLUtils::Close()
{
   INHIBIT(std::cout << "SDLUtils::Close()" << std::endl;)
   // Textures
   for (std::map<std::string, SDL_Texture*>::iterator it = g_textures.begin(); it != g_textures.end(); ++it)
      SDL_DestroyTexture(it->second);
   // Renderer
   if (g_renderer != NULL)
   {
      SDL_DestroyRenderer(g_renderer);
      g_renderer = NULL;
   }
   // Window
   if (g_window != NULL)
   {
      SDL_DestroyWindow(g_window);
      g_window = NULL;
   }
   // Joystick
   if (g_joystick != NULL)
   {
      SDL_JoystickClose(g_joystick);
      g_joystick = NULL;
   }
   // SDL_image
   IMG_Quit();
   // SDL
   SDL_Quit();
   // romfs
   #ifdef __SWITCH__
   romfsExit();
   #endif
}

//------------------------------------------------------------------------------

// Load a texture
SDL_Texture* SDLUtils::LoadTexture(const std::string &p_path)
{
   INHIBIT(std::cout << "SDLUtils::LoadTexture(" << p_path << ")" << std::endl;)
   SDL_Texture* texture = NULL;
   SDL_Surface* surface = IMG_Load(p_path.c_str());
   if (surface == NULL)
   {
      std::cerr << "Unable to load image '" << p_path << "'! SDL_Error: " << SDL_GetError() << std::endl;
      return NULL;
   }
   texture = SDL_CreateTextureFromSurface(g_renderer, surface);
   if (texture == NULL)
   {
      std::cerr << "Unable to create texture from '" << p_path << "'! SDL_Error: " << SDL_GetError() << std::endl;
      return NULL;
   }
   SDL_FreeSurface(surface);
   return texture;
}

//------------------------------------------------------------------------------

// Return a texture, load it if necessary
SDL_Texture* SDLUtils::GetTexture(const std::string &p_path)
{
   INHIBIT(std::cout << "SDLUtils::GetTexture(" << p_path << ")" << std::endl;)
   // Search texture
   std::map<std::string, SDL_Texture*>::iterator it = g_textures.find(p_path);
   if (it != g_textures.end())
      return it->second;
   // First time asking for this texture => load it
   SDL_Texture *tex = LoadTexture(p_path);
   if (tex != NULL)
      g_textures.insert(std::pair<std::string, SDL_Texture*>(p_path, tex));
   return tex;
}
