#include "def.h"

//------------------------------------------------------------------------------

// Constructor
Sprite::Sprite(const std::string &p_textureFile, int p_width, int p_height, Planet *p_planet):
   m_texture(NULL),
   m_state(SpriteState_Idle),
   m_x(0.0),
   m_y(0.0),
   m_width(p_width),
   m_height(p_height),
   m_accelRun(0.0),
   m_speedRun(0.0),
   m_accelX(0.0),
   m_accelY(0.0),
   m_speedX(0.0),
   m_speedY(0.0),
   m_planet(p_planet),
   m_angle(-M_PI_2),
   m_rotationSpeed(0.0),
   m_animId(0),
   m_animStep(0),
   m_animNbSteps(0),
   m_animSpeed(0),
   m_frameCounter(0),
   m_flip(SDL_FLIP_NONE)
{
   m_texture = SDLUtils::GetTexture(p_textureFile);
   START_ANIM_IDLE;
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
   switch (m_state)
   {
      case SpriteState_Idle:
      case SpriteState_Run:
         if (p_event.type == SDL_KEYDOWN && p_event.key.repeat == 0 && p_event.key.keysym.sym == SDLK_w)
         {
            START_ANIM_STRIKE;
            m_state = SpriteState_Strike;
         }
         break;
      case SpriteState_Strike:
         break;
      case SpriteState_Jump:
         break;
   }
}

//------------------------------------------------------------------------------

// Update sprite state at each frame
void Sprite::Update()
{
   // Update sprite depending on the current state
   switch (m_state)
   {
      //========================================================================c
      case SpriteState_Idle:
      case SpriteState_Run:

         // Move left / right
         MoveOnGround();

         // ----------------
         // Update animation
         // ----------------
         if (m_speedRun == 0.0)
         {
            if (m_state != SpriteState_Idle)
            {
               START_ANIM_IDLE;
               m_state = SpriteState_Idle;
            }
         }
         else
         {
            if (m_state != SpriteState_Run)
            {
               START_ANIM_RUN;
               m_state = SpriteState_Run;
            }
            m_animSpeed = RUN_SPEED_MAX - abs(round(m_speedRun));
         }
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

         break;

      //========================================================================
      case SpriteState_Strike:

         // Move left / right
         MoveOnGround();

         // ----------------
         // Update animation
         // ----------------
         if (m_frameCounter > m_animSpeed)
         {
            ++m_animStep;
            if (m_animStep >= m_animNbSteps)
            {
               // Strike animation is over => jump!
               START_ANIM_JUMP;
               m_planet = NULL;
               m_state = SpriteState_Jump;
               // Tangent speed vector
               m_speedX = abs(m_speedRun) * cos(m_flip == SDL_FLIP_NONE ? m_angle + M_PI_2 : m_angle - M_PI_2);
               m_speedY = abs(m_speedRun) * sin(m_flip == SDL_FLIP_NONE ? m_angle + M_PI_2 : m_angle - M_PI_2);
               // Vertical speed vector
               m_speedX += 4.0 * cos(m_angle);
               m_speedY += 4.0 * sin(m_angle);
               // Rotation speed
               m_rotationSpeed = m_speedRun * M_PI / 180.0;
            }
            m_frameCounter = 0;
         }
         else
         {
            ++m_frameCounter;
         }

         break;

      //========================================================================
      case SpriteState_Jump:

         // Float in space until collision
         m_planet = MoveInSpace();
         if (m_planet != NULL)
         {
            // Land on a planet
            INHIBIT(std::cout << "Collision detected!" << std::endl;)
            if (m_speedRun < 1.0 && m_speedRun > -1.0)
            {
               m_speedRun = 0.0;
               START_ANIM_IDLE;
               m_state = SpriteState_Idle;
            }
            else
            {
               m_flip = m_speedRun > 0.0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
               START_ANIM_RUN;
               m_state = SpriteState_Run;
            }
            break;
         }

         // Next animation step
         if (m_frameCounter > m_animSpeed)
         {
            if (m_animStep + 1 >= m_animNbSteps)
            {
               // Animation stops at last frame
               m_animSpeed = 0;
            }
            else
            {
               ++m_animStep;
               m_frameCounter = 0;
            }
         }
         else
         {
            ++m_frameCounter;
         }

         break;
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
   SDL_RenderCopyEx(g_renderer, m_texture, &srcRect, &destRect, (m_angle * 180 / M_PI) + 90.0, NULL, m_flip);
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

//------------------------------------------------------------------------------

// Set x and y coordinates
void Sprite::SetPosition(const double &p_x, const double &p_y)
{
   INHIBIT(std::cout << "Sprite::SetPosition(" << p_x << ", " << p_y << ")" << std::endl;)
   m_x = p_x;
   m_y = p_y;
}

//------------------------------------------------------------------------------

// Move sprite with left / right buttons
void Sprite::MoveOnGround()
{
   // -------------------
   // Update acceleration
   // -------------------
   if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
   {
      m_accelRun = RUN_ACCELERATION;
      if (m_flip != SDL_FLIP_NONE)
         m_flip = SDL_FLIP_NONE;
   }
   else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
   {
      m_accelRun = -RUN_ACCELERATION;
      if (m_flip != SDL_FLIP_HORIZONTAL)
         m_flip = SDL_FLIP_HORIZONTAL;
   }
   else
   {
      m_accelRun = 0.0;
   }

   // -------------------
   // Update speed
   // -------------------
   if (m_accelRun == 0.0 && m_speedRun != 0.0)
   {
      // Deceleration
      m_speedRun += m_speedRun > 0.0 ? -RUN_DECELERATION : RUN_DECELERATION;
      if (m_speedRun < RUN_DECELERATION && m_speedRun > -RUN_DECELERATION)
         m_speedRun = 0.0;
   }
   else
   {
      // Acceleration
      if (m_speedRun * m_accelRun < 0.0)
         m_speedRun += 2 * m_accelRun;
      else
         m_speedRun += m_accelRun;
      if (m_speedRun > RUN_SPEED_MAX)
         m_speedRun = RUN_SPEED_MAX;
      else if (m_speedRun < -RUN_SPEED_MAX)
         m_speedRun = -RUN_SPEED_MAX;
   }

   // -------------------
   // Update position
   // -------------------
   m_angle += m_speedRun / m_planet->m_radius;
   m_x = m_planet->m_x + m_planet->m_radius + ((m_planet->m_radius + (m_height / 2) - GAP_SPRITE_GROUND) * cos(m_angle)) - (m_width / 2);
   m_y = m_planet->m_y + m_planet->m_radius + ((m_planet->m_radius + (m_height / 2) - GAP_SPRITE_GROUND) * sin(m_angle)) - (m_height / 2);
}

//------------------------------------------------------------------------------

// Move sprite in space
Planet *Sprite::MoveInSpace()
{
   // ---------------------------
   // Update acceleration & speed
   // ---------------------------
   double spriteCenterX = m_x + (m_width / 2.0);
   double spriteCenterY = m_y + (m_height / 2.0);
   double distanceSpritePlanet = 0.0;
   for (std::vector<Planet*>::iterator planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
   {
      distanceSpritePlanet = sqrt(pow(spriteCenterX - (*planetIt)->m_centerX, 2) + pow(spriteCenterY - (*planetIt)->m_centerY, 2));
      if (distanceSpritePlanet < (*planetIt)->m_radius + GAP_SPRITE_CENTER_GROUND)
      {
         // Angle of rotation at contact
         m_angle = atan((spriteCenterY - (*planetIt)->m_centerY) / (spriteCenterX - (*planetIt)->m_centerX));
         if (spriteCenterX < (*planetIt)->m_centerX)
            m_angle += M_PI;
         // Run speed at contact
         m_speedRun = (m_speedX * sin(-m_angle) + m_speedY * cos(-m_angle)) * 0.7;
         if (m_speedRun > RUN_SPEED_MAX)
            m_speedRun = RUN_SPEED_MAX;
         else if (m_speedRun < -RUN_SPEED_MAX)
            m_speedRun = -RUN_SPEED_MAX;
         return *planetIt;
      }
      m_accelX = ((*planetIt)->m_centerX - spriteCenterX) * (*planetIt)->m_mass / pow(distanceSpritePlanet, 2);
      m_accelY = ((*planetIt)->m_centerY - spriteCenterY) * (*planetIt)->m_mass / pow(distanceSpritePlanet, 2);
      m_speedX += m_accelX;
      m_speedY += m_accelY;
   }

   // -------------------
   // Update position
   // -------------------
   m_x += m_speedX;
   m_y += m_speedY;
   m_angle += m_rotationSpeed;

   return NULL;
}
