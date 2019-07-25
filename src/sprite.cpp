#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Sprite::Sprite(const std::string &p_textureFile, int p_width, int p_height):
   m_texture(NULL),
   m_x(0.0),
   m_y(0.0),
   m_width(p_width),
   m_height(p_height),
   m_runAccel(0.0),
   m_runSpeed(0.0),
   m_planet(NULL),
   m_angle(-M_PI_2),
   m_animId(0),
   m_animStep(0),
   m_animNbSteps(0),
   m_animSpeed(0),
   m_frameCounter(0),
   m_flip(SDL_FLIP_NONE)
{
   m_texture = SDLUtils::LoadTexture(p_textureFile);
}

//------------------------------------------------------------------------------

// Destructor
Sprite::~Sprite()
{
   if (m_texture != NULL)
   {
      SDL_DestroyTexture(m_texture);
      m_texture = NULL;
   }
}

//------------------------------------------------------------------------------

// Update sprite state at each frame
void Sprite::Update()
{
   // When on ground
   if (m_planet != NULL)
   {
      // Handle key input
      if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
      {
         m_runAccel = RUN_ACCELERATION;
         if (m_flip != SDL_FLIP_NONE)
            m_flip = SDL_FLIP_NONE;
         if (m_animId != 1)
            StartAnim(1, 8, 3);
      }
      else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
      {
         m_runAccel = -RUN_ACCELERATION;
         if (m_flip != SDL_FLIP_HORIZONTAL)
            m_flip = SDL_FLIP_HORIZONTAL;
         if (m_animId != 1)
            StartAnim(1, 8, 3);
      }
      else
      {
         m_runAccel = 0.0;
      }

      // Update speed
      if (m_runAccel == 0.0 && m_runSpeed != 0.0)
      {
         // Deceleration
         m_runSpeed += m_runSpeed > 0.0 ? -RUN_DECELERATION : RUN_DECELERATION;
         if (m_runSpeed < RUN_DECELERATION && m_runSpeed > -RUN_DECELERATION)
            m_runSpeed = 0.0;
      }
      else
      {
         // Acceleration
         if (m_runSpeed * m_runAccel < 0.0)
            m_runSpeed += 2 * m_runAccel;
         else
            m_runSpeed += m_runAccel;
         if (m_runSpeed > RUN_SPEED_MAX)
            m_runSpeed = RUN_SPEED_MAX;
         else if (m_runSpeed < -RUN_SPEED_MAX)
            m_runSpeed = -RUN_SPEED_MAX;
      }

      // Update Position
      m_angle += m_runSpeed / m_planet->m_radius;
      m_x = m_planet->m_x + m_planet->m_radius + ((m_planet->m_radius + (m_height / 2)) * cos(m_angle)) - (m_width / 2);
      m_y = m_planet->m_y + m_planet->m_radius + ((m_planet->m_radius + (m_height / 2)) * sin(m_angle)) - (m_height / 2);

      // Update animation
      if (m_runSpeed == 0.0)
      {
         if (m_animId != 0)
            StartAnim(0, 6, 7);
      }
      else
      {
         m_animSpeed = RUN_SPEED_MAX - abs(round(m_runSpeed)) + 1;
      }
      if (m_frameCounter > m_animSpeed)
      {
         // Next animation step
         m_animStep = (m_animStep + 1) % m_animNbSteps;
         m_frameCounter = 0;
      }
      else
      {
         ++m_frameCounter;
      }
   }

}

//------------------------------------------------------------------------------

// Start animation
void Sprite::StartAnim(int p_animId, int p_nbSteps, int p_speed)
{
   m_animId = p_animId;
   m_animStep = 0;
   m_animNbSteps = p_nbSteps;
   m_animSpeed = p_speed;
   m_frameCounter = 0;
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
   SDL_RenderCopyEx(g_renderer, m_texture, &srcRect, &destRect, (m_angle * 180 / M_PI) + 90.0, NULL, m_flip);
}

//------------------------------------------------------------------------------

// Set x and y coordinates
void Sprite::SetPosition(const double &p_x, const double &p_y)
{
   m_x = p_x;
   m_y = p_y;
}
