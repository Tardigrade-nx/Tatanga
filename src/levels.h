#ifndef _LEVELS_H_
#define _LEVELS_H_

namespace Levels
{

   // Load a level from the level file
   bool load(int p_levelNumber);

   // Unload current level
   void unload();

   // Get number of levels in the level file
   int number();

}

#endif
