#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include "levels.h"
#include "def.h"
#include "planet.h"
#include "sprite.h"

#define LEVELS_FILE "levels.dat"

//------------------------------------------------------------------------------

// Load a level from the level file
bool Levels::load(int p_levelNumber)
{
   INHIBIT(std::cout << "Levels::load(" << p_levelNumber << ")" << std::endl;)
   // Unload existing level
   unload();
   if (p_levelNumber < 1)
      return false;
   // Read level line in file
   std::ifstream ifs(LEVELS_FILE);
   if (! ifs.is_open())
   {
      std::cerr << "Levels::load: unable to read file '" << LEVELS_FILE << "'"<< std::endl;
      return false;
   }
   std::string line("");
   int levelNumber(0);
   while (levelNumber < p_levelNumber && ! ifs.eof())
   {
      std::getline(ifs, line);
      if (line.empty() || line.at(0) == '#')
         continue;
      ++levelNumber;
   }
   if (levelNumber != p_levelNumber)
   {
      std::cerr << "Levels::load: level '" << p_levelNumber << "' not found in file '" << LEVELS_FILE << "'"<< std::endl;
      return false;
   }
   // Read planets and cherries in line
   std::string id("");
   std::string name("");
   int width(0);
   double mass(0.0);
   double posX(0.0);
   double posY(0.0);
   // TODO

   return true;
}

//------------------------------------------------------------------------------

// Unload current level
void Levels::unload()
{
   // Delete planets
   for (std::list<Planet*>::iterator planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
      delete *planetIt;
   g_planets.clear();
   // Delete cherries
   for (std::list<Sprite*>::iterator spriteIt = g_cherries.begin(); spriteIt != g_cherries.end(); ++spriteIt)
      delete *spriteIt;
   g_cherries.clear();
}

//------------------------------------------------------------------------------

// Get number of levels in the level file
int Levels::number()
{
   return 0;
}
