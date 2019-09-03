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

// Select a sprite with the mouse, for level editor
INHIBIT(
Sprite *getClickedSprite(int p_x, int p_y)
{
   for (std::list<Sprite*>::iterator spriteIt = g_cherries.begin(); spriteIt != g_cherries.end(); ++spriteIt)
   {
      if (p_x >= (*spriteIt)->m_x && p_x <= (*spriteIt)->m_x + (*spriteIt)->m_width && p_y >= (*spriteIt)->m_y && p_y <= (*spriteIt)->m_y + (*spriteIt)->m_height)
         return *spriteIt;
   }
   for (std::list<Planet*>::iterator planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
   {
      if (p_x >= (*planetIt)->m_x && p_x <= (*planetIt)->m_x + (*planetIt)->m_width && p_y >= (*planetIt)->m_y && p_y <= (*planetIt)->m_y + (*planetIt)->m_height)
         return *planetIt;
   }
   return NULL;
}
)

//------------------------------------------------------------------------------

int main(int argc, char* args[])
{
   // Init SDL
   if (! SDLUtils::Init())
   {
      SDLUtils::Close();
      return 1;
   }

   INHIBIT(Sprite *mouseSelectedSprite = NULL;)

   // Load first level
   int levelNumber = 1;
   Levels::Load(levelNumber);

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
         // Level editor, only active in debug mode
         else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
         {
            // Click on a sprite
            mouseSelectedSprite = getClickedSprite(e.button.x, e.button.y);
            if (mouseSelectedSprite != NULL)
               mouseSelectedSprite->SetPosition(e.button.x - mouseSelectedSprite->m_width / 2, e.button.y - mouseSelectedSprite->m_height / 2);
         }
         else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
         {
            // Release the selected sprite
            mouseSelectedSprite = NULL;
         }
         else if (e.type == SDL_MOUSEMOTION && mouseSelectedSprite != NULL)
         {
            // Move the selected sprite
            mouseSelectedSprite->SetPosition(e.button.x - mouseSelectedSprite->m_width / 2, e.button.y - mouseSelectedSprite->m_height / 2);
         }
         else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
         {
            // Print current level line
            Levels::Print();
         }
         else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_c)
         {
            // Add a cherry
            Sprite *cherry = new Sprite("res/cherry.png", 16, 16);
            cherry->SetPosition(SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 2 - 8);
            cherry->StartAnim(0, 6, 8);
            g_cherries.push_back(cherry);
         }
         else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_n)
         {
            // Next level
            ++levelNumber;
            Levels::Load(levelNumber);
            tatanga->Reset(*g_planets.begin());
         }
         else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_b)
         {
            // Previous level
            --levelNumber;
            Levels::Load(levelNumber);
            tatanga->Reset(*g_planets.begin());
         }
         else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_r)
         {
            // Restart level
            Levels::Load(levelNumber);
            tatanga->Reset(*g_planets.begin());
         }
         )
         else
         {
            tatanga->Handle(e);
         }
      }
      // Update Tatanga
      tatanga->Update();
      if (tatanga->m_planet != NULL && !tatanga->m_planet->m_landing)
      {
         // Tatanga landed on a deadly planet => restart level
         Levels::Load(levelNumber);
         tatanga->Reset(*g_planets.begin());
      }
      // Update cherries
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
   Levels::Unload();
   SDLUtils::Close();
   return 0;
}
