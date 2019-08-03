#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include <string>
#include <SDL2/SDL.h>

namespace SDLUtils
{

   // Init SDL
   bool Init();

   // Close SDL
   void Close();

   // Return a texture, load it if necessary
   SDL_Texture* GetTexture(const std::string &p_path);

   // Load a texture
   SDL_Texture* LoadTexture(const std::string &p_path);

}

#endif
