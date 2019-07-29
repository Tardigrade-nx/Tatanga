#include "def.h"

//------------------------------------------------------------------------------

// Globals
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
std::vector<Planet*> g_planets;

//------------------------------------------------------------------------------

int main(int argc, char* args[])
{
   // Init SDL
   if (! SDLUtils::Init())
   {
      SDLUtils::Close();
      return 1;
   }

   // Create planets
   Planet *planet = new Planet("res/planet.png", 40.0);
   planet->SetPosition((SCREEN_WIDTH / 2) - planet->m_radius, (SCREEN_HEIGHT / 2) - planet->m_radius);
   g_planets.push_back(planet);

   // Create Sprite
   Sprite tatanga("res/tatanga.png", 64, 64, *g_planets.begin());

   // Main loop
   SDL_Event e;
   bool loop = true;
   std::vector<Planet*>::iterator planetIt;
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
         else
         {
            tatanga.Handle(e);
         }
      }
      // Update
      tatanga.Update();
      // Render
      SDL_RenderClear(g_renderer);
      for (planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
         (*planetIt)->Render();
      tatanga.Render();
      SDL_RenderPresent(g_renderer);
   }

   // Clean up and quit
   for (planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
      delete (*planetIt);
   SDLUtils::Close();
   return 0;
}
