#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include "def.h"
#include "sdlutils.h"
#include "planet.h"
#include "tatanga.h"
#include "levels.h"

//------------------------------------------------------------------------------

// Globals
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
std::map<std::string, SDL_Texture*> g_textures;
std::list<Planet*> g_planets;
std::list<Sprite*> g_cherries;

//------------------------------------------------------------------------------

int main(int argc, char* args[])
{
   // Init SDL
   if (! SDLUtils::Init())
   {
      SDLUtils::Close();
      return 1;
   }

   // Load first level
   Levels::load(2);

   // Create Tatanga
   Tatanga *tatanga = new Tatanga("res/tatanga.png", 64, 64, *g_planets.begin());

   // Main loop
   SDL_Event e;
   bool loop = true;
   std::list<Planet*>::iterator planetIt;
   std::list<Sprite*>::iterator spriteIt;
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
         INHIBIT(
         // Level editor
         else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
         {
            Planet *planet = *g_planets.begin();
            planet->SetPosition(e.button.x - planet->m_radius, e.button.y - planet->m_radius);
         }
         )
         else
         {
            tatanga->Handle(e);
         }
      }
      // Update
      tatanga->Update();
      for (spriteIt = g_cherries.begin(); spriteIt != g_cherries.end();)
      {
         (*spriteIt)->Update();
         // Collision Tatanga / cherry
         if (sqrt(pow(tatanga->m_centerX - (*spriteIt)->m_centerX, 2) + pow(tatanga->m_centerY - (*spriteIt)->m_centerY, 2)) < 20.0)
         {
            spriteIt = g_cherries.erase(spriteIt);
            INHIBIT(std::cout << "Cherry get! Remaining: " << g_cherries.size() << std::endl;)
         }
         else
         {
            ++spriteIt;
         }
      }
      // Render
      SDL_RenderClear(g_renderer);
      for (planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
         (*planetIt)->Render();
      for (spriteIt = g_cherries.begin(); spriteIt != g_cherries.end(); ++spriteIt)
         (*spriteIt)->Render();
      tatanga->Render();
      SDL_RenderPresent(g_renderer);
   }

   // Clean up and quit
   delete tatanga;
   Levels::unload();
   SDLUtils::Close();
   return 0;
}
