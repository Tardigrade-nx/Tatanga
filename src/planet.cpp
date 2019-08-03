#include "planet.h"
#include "sdlutils.h"
#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Planet::Planet(const std::string &p_textureFile, int p_width, double p_mass):
   m_texture(NULL),
   m_x(0.0),
   m_y(0.0),
   m_centerX(0.0),
   m_centerY(0.0),
   m_diameter(p_width),
   m_radius(p_width / 2.0),
   m_mass(p_mass)
{
   m_texture = SDLUtils::GetTexture(p_textureFile);
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
   m_centerX = m_x + m_radius;
   m_centerY = m_y + m_radius;
}
