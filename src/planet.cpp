#include <cmath>
#include "planet.h"
#include "sdlutils.h"
#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Planet::Planet(const std::string &p_textureFile, int p_width, const double &p_mass, bool p_landing, const double &p_radius, const double &p_rotation):
   Sprite::Sprite(p_textureFile, p_width, p_width),
   m_name(""),
   m_radius(p_radius),
   m_mass(p_mass),
   m_landing(p_landing),
   m_rotation(p_rotation)
{
   // Name of the planet = texture file name, minus path and extension
   size_t pos = p_textureFile.rfind('/');
   if (pos == std::string::npos)
      pos = 0;
   m_name = p_textureFile.substr(pos + 1, p_textureFile.rfind('.') - pos - 1);
}

//------------------------------------------------------------------------------

// Destructor
Planet::~Planet()
{
}

//------------------------------------------------------------------------------

// Update planet state at each frame
void Planet::Update()
{
   m_angle += m_rotation;
}

//------------------------------------------------------------------------------

// Render planet
void Planet::Render()
{
   // Destination rectangle
   SDL_Rect destRect;
   destRect.x = static_cast<int>(round(m_x));
   destRect.y = static_cast<int>(round(m_y));
   destRect.w = m_width;
   destRect.h = m_width;
   // Render planet
   if (m_rotation == 0.0)
      SDL_RenderCopy(g_renderer, m_texture, NULL, &destRect);
   else
      SDL_RenderCopyEx(g_renderer, m_texture, NULL, &destRect, (m_angle * 180.0 / M_PI) + 90.0, NULL, m_flip);
}
