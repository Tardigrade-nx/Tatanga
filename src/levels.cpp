#include <list>
#include <fstream>
#include <sstream>
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
   {
      std::cerr << "Levels::load: invalid level number: '" << p_levelNumber << "'"<< std::endl;
      return false;
   }

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
   char id(0);
   std::string name("");
   int width(0);
   double mass(0.0);
   double posX(0.0);
   double posY(0.0);
   std::istringstream iss(line);
   Planet *planet = NULL;
   Sprite *cherry = NULL;
   while (! iss.eof())
   {
      // Read element id
      iss >> id;
      switch (id)
      {
         case 'P':
            // Add planet
            iss >> name;
            iss >> width;
            iss >> mass;
            iss >> posX;
            iss >> posY;
            INHIBIT(std::cout << "Adding planet '" << name << "' " << width << " " << mass << " " << posX << " " << posY << std::endl;)
            planet = new Planet(std::string("res/") + name + ".png", width, mass);
            planet->SetPosition(posX, posY);
            g_planets.push_back(planet);
            break;
         case 'C':
            // Add cherry
            iss >> posX;
            iss >> posY;
            INHIBIT(std::cout << "Adding cherry " << posX << " " << posY << std::endl;)
            cherry = new Sprite("res/cherry.png", 16, 16);
            cherry->SetPosition(posX, posY);
            cherry->StartAnim(0, 6, 8);
            g_cherries.push_back(cherry);
            break;
         default:
            std::cerr << "Levels::load: invalid format for file '" << LEVELS_FILE << "'"<< std::endl;
            return false;
      }
   }

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
