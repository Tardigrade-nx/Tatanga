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

   // Create planets
   Planet *planet = new Planet("res/earth.png", 200, 30.0);
   planet->SetPosition(540, 260);
   g_planets.push_back(planet);
   //~ Planet *planet = new Planet("res/earth.png", 200, 30.0);
   //~ planet->SetPosition((SCREEN_WIDTH / 2) - planet->m_radius - 400, (SCREEN_HEIGHT / 2) - planet->m_radius + 150);
   //~ g_planets.push_back(planet);
   //~ planet = new Planet("res/moon.png", 130, 27.0);
   //~ planet->SetPosition((SCREEN_WIDTH / 2) - planet->m_radius, (SCREEN_HEIGHT / 2) - planet->m_radius - 200);
   //~ g_planets.push_back(planet);
   //~ planet = new Planet("res/planet.png", 200, 30.0);
   //~ planet->SetPosition((SCREEN_WIDTH / 2) - planet->m_radius + 400, (SCREEN_HEIGHT / 2) - planet->m_radius + 100);
   //~ g_planets.push_back(planet);

   // Create Tatanga
   Tatanga *tatanga = new Tatanga("res/tatanga.png", 64, 64, *g_planets.begin());

   // Create cherries
   Sprite *cherry;
   cherry = new Sprite("res/cherry.png", 16, 16);
   cherry->SetPosition(632, 112);
   cherry->StartAnim(0, 6, 8);
   g_cherries.push_back(cherry);
   cherry = new Sprite("res/cherry.png", 16, 16);
   cherry->SetPosition(738, 401);
   cherry->StartAnim(0, 6, 8);
   g_cherries.push_back(cherry);
   cherry = new Sprite("res/cherry.png", 16, 16);
   cherry->SetPosition(528, 463);
   cherry->StartAnim(0, 6, 8);
   g_cherries.push_back(cherry);

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
