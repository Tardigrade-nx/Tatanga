#include "def.h"

//------------------------------------------------------------------------------

// Globals
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

//------------------------------------------------------------------------------

int main(int argc, char* args[])
{
   // Init SDL
   if (! SDLUtils::Init())
   {
      SDLUtils::Close();
      return 1;
   }

   // Create planet
   Planet planet("res/planet.png", 10.0);
   planet.SetPosition((SCREEN_WIDTH / 2) - planet.m_radius, (SCREEN_HEIGHT / 2) - planet.m_radius);

   // Create Sprite
   Sprite tatanga("res/tatanga.png", 40, 40);
   tatanga.m_planet = &planet;
   tatanga.StartAnim(0, 6, 7);
   tatanga.SetPosition(planet.m_x + planet.m_radius - (tatanga.m_width / 2), planet.m_y - tatanga.m_height);

   // Main loop
   SDL_Event e;
   bool loop = true;
   while (loop)
   {
      // Handle events
      while (SDL_PollEvent(&e) != 0 )
      {
         // Quit
         if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_ESCAPE))
         {
            loop = false;
         }
      }
      // Update
      planet.Update();
      tatanga.Update();
      // Render
      SDL_RenderClear(g_renderer);
      planet.Render();
      tatanga.Render();
      SDL_RenderPresent(g_renderer);
   }

   // Clean up and quit
   SDLUtils::Close();
   return 0;
}
