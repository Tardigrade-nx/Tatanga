#include <iostream>
#include "sprite.h"
#include "sdlutils.h"
#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Sprite::Sprite(const std::string &p_textureFile, int p_width, int p_height):
   m_texture(NULL),
   m_x(0.0),
   m_y(0.0),
   m_centerX(p_width / 2.0),
   m_centerY(p_height / 2.0),
   m_width(p_width),
   m_height(p_height),
   m_angle(-M_PI_2),
   m_animId(0),
   m_animStep(0),
   m_animNbSteps(0),
   m_animSpeed(0),
   m_frameCounter(0),
   m_flip(SDL_FLIP_NONE)
{
   m_texture = SDLUtils::GetTexture(p_textureFile);
}

//------------------------------------------------------------------------------

// Destructor
Sprite::~Sprite()
{
}

//------------------------------------------------------------------------------

// Handle events
void Sprite::Handle(const SDL_Event &p_event)
{
}

//------------------------------------------------------------------------------

// Update sprite state at each frame
void Sprite::Update()
{
   // Next animation step
   if (m_frameCounter > m_animSpeed)
   {
      m_animStep = (m_animStep + 1) % m_animNbSteps;
      m_frameCounter = 0;
   }
   else
   {
      ++m_frameCounter;
   }
}

//------------------------------------------------------------------------------

// Render sprite
void Sprite::Render()
{
   // Source and destination rectangles
   SDL_Rect srcRect;
   srcRect.x = m_animStep * m_width;
   srcRect.y = m_animId * m_height;
   srcRect.w = m_width;
   srcRect.h = m_height;
   SDL_Rect destRect;
   destRect.x = static_cast<int>(round(m_x));
   destRect.y = static_cast<int>(round(m_y));
   destRect.w = m_width;
   destRect.h = m_height;
   // Render sprite
   SDL_RenderCopyEx(g_renderer, m_texture, &srcRect, &destRect, (m_angle * 180.0 / M_PI) + 90.0, NULL, m_flip);
}

//------------------------------------------------------------------------------

// Set x and y coordinates
void Sprite::SetPosition(const double &p_x, const double &p_y)
{
   INHIBIT(std::cout << "Sprite::SetPosition(" << p_x << ", " << p_y << ")" << std::endl;)
   m_x = p_x;
   m_y = p_y;
   m_centerX = m_x + m_width / 2.0;
   m_centerY = m_y + m_height / 2.0;
}

//------------------------------------------------------------------------------

// Start animation
void Sprite::StartAnim(int p_animId, int p_nbSteps, int p_speed)
{
   INHIBIT(std::cout << "Sprite::StartAnim(" << p_animId << ", " << p_nbSteps << ", " << p_speed << ")" << std::endl;)
   m_animId = p_animId;
   m_animStep = 0;
   m_animNbSteps = p_nbSteps;
   m_animSpeed = p_speed;
   m_frameCounter = 0;
}
