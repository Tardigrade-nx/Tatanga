#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include "def.h"

namespace SDLUtils
{

   // Init SDL
   bool Init();

   // Close SDL
   void Close();

   // Load a texture
   SDL_Texture* LoadTexture(const std::string &p_path);

}

#endif
