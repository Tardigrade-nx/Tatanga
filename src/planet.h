#ifndef _PLANET_H_
#define _PLANET_H_

#include <string>
#include <SDL2/SDL.h>

class Planet
{

//------------------------------------------------------------------------------

   public:

   // Constructor
   Planet(const std::string &p_textureFile, int p_width, double p_mass);

   // Destructor
   virtual ~Planet();

   // Update planet state at each frame
   void Update();

   // Render planet
   void Render();

   // Set x and y coordinates
   void SetPosition(const double &p_x, const double &p_y);

//------------------------------------------------------------------------------

   public:

   // Texture containing the planet image
   SDL_Texture *m_texture;

   // Coordinates of the planet
   double m_x;
   double m_y;
   double m_centerX;
   double m_centerY;

   // Diameter and radius of the planet
   int m_diameter;
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
