#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Planet::Planet(const std::string &p_textureFile, double m_mass):
   m_texture(NULL),
   m_x(0.0),
   m_y(0.0),
   m_diameter(0),
   m_radius(0),
   m_mass(0.0)
{
   m_texture = SDLUtils::LoadTexture(p_textureFile);
   SDL_QueryTexture(m_texture, NULL, NULL, &m_diameter, NULL);
   m_radius = m_diameter / 2;
}

//------------------------------------------------------------------------------

// Destructor
Planet::~Planet()
{
   if (m_texture != NULL)
   {
      SDL_DestroyTexture(m_texture);
      m_texture = NULL;
   }
}

//------------------------------------------------------------------------------

// Update planet state at each frame
void Planet::Update()
{
}

//------------------------------------------------------------------------------

// Render planet
void Planet::Render()
{
   // Destination rectangle
   SDL_Rect destRect;
   destRect.x = static_cast<int>(round(m_x));
   destRect.y = static_cast<int>(round(m_y));
   destRect.w = m_diameter;
   destRect.h = m_diameter;
   // Render planet
   SDL_RenderCopy(g_renderer, m_texture, NULL, &destRect);
}

//------------------------------------------------------------------------------

// Set x and y coordinates
void Planet::SetPosition(const double &p_x, const double &p_y)
{
   m_x = p_x;
   m_y = p_y;
}
