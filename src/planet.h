#ifndef _PLANET_H_
#define _PLANET_H_

#include <string>
#include <SDL2/SDL.h>
#include "sprite.h"

class Planet: public Sprite
{

//------------------------------------------------------------------------------

   public:

   // Constructor
   Planet(const std::string &p_textureFile, int p_width, double p_mass);

   // Destructor
   virtual ~Planet();

   // Update planet state at each frame
   virtual void Update();

   // Render planet
   virtual void Render();

//------------------------------------------------------------------------------

   public:

   // Name of the planet
   std::string m_name;

   // Diameter and radius of the planet
   double m_radius;

   // Mass of the planet
   double m_mass;

//------------------------------------------------------------------------------

   private:

   // Forbidden
   Planet();
   Planet(const Planet&);
   const Planet& operator=(const Planet&);

//------------------------------------------------------------------------------
};

#endif
