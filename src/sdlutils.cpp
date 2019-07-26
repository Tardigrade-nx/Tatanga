#include "def.h"

//------------------------------------------------------------------------------

// Init SDL
bool SDLUtils::Init()
{
   INHIBIT(std::cout << "SDLUtils::Init()" << std::endl;)
   // Initialize SDL
   if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
   // Create window
   g_window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
   SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   return true;
}

//------------------------------------------------------------------------------

// Close SDL
void SDLUtils::Close()
{
   INHIBIT(std::cout << "SDLUtils::Close()" << std::endl;)
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
   // SDL_image
   IMG_Quit();
   // SDL
   SDL_Quit();
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
