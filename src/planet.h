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
   Planet(const std::string &p_textureFile, int p_width, const double &p_mass, bool p_landing, const double &p_radius, const double &p_rotation);

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

   // Radius of the planet, used for collision detection
   double m_radius;

   // Mass of the planet
   double m_mass;

   // Is it allowed to land on it, or not
   bool m_landing;

   // Angle of rotation
   double m_rotation;

//------------------------------------------------------------------------------

   private:

   // Forbidden
   Planet();
   Planet(const Planet&);
   const Planet& operator=(const Planet&);

//------------------------------------------------------------------------------
};

#endif
