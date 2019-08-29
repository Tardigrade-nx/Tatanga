#ifndef _LEVELS_H_
#define _LEVELS_H_

namespace Levels
{

   // Load a level from the level file
   bool Load(int p_levelNumber);

   // Unload current level
   void Unload();

   // Get number of levels in the level file
   int Number();

   // Print current level
   void Print();

}

#endif
