#include <iostream>
#include "planet.h"
#include "tatanga.h"
#include "def.h"

//------------------------------------------------------------------------------

// Constants for Tatanga
#define GAP_SPRITE_GROUND           12
#define GAP_SPRITE_CENTER_GROUND    19
#define RUN_SPEED_MAX               6.0
#define RUN_ACCELERATION            0.1
#define RUN_DECELERATION            0.1
#define START_ANIM_IDLE             StartAnim(0, 6, 7)
#define START_ANIM_RUN              StartAnim(1, 8, 3)
#define START_ANIM_STRIKE           StartAnim(2, 2, 5)
#define START_ANIM_JUMP             StartAnim(3, 3, 8)

//------------------------------------------------------------------------------

// Constructor
Tatanga::Tatanga(const std::string &p_textureFile, int p_width, int p_height, Planet *p_planet):
   Sprite::Sprite(p_textureFile, p_width, p_height),
   m_state(TatangaState_Idle),
   m_accelRun(0.0),
   m_speedRun(0.0),
   m_accelX(0.0),
   m_accelY(0.0),
   m_speedX(0.0),
   m_speedY(0.0),
   m_planet(p_planet),
   m_rotationSpeed(0.0)
{
   START_ANIM_IDLE;
}

//------------------------------------------------------------------------------

// Destructor
Tatanga::~Tatanga()
{
}

//------------------------------------------------------------------------------

// Handle events
void Tatanga::Handle(const SDL_Event &p_event)
{
   switch (m_state)
   {
      case TatangaState_Idle:
      case TatangaState_Run:
         if (p_event.type == SDL_KEYDOWN && p_event.key.repeat == 0 && p_event.key.keysym.sym == SDLK_w)
         {
            START_ANIM_STRIKE;
            m_state = TatangaState_Strike;
         }
         break;
      case TatangaState_Strike:
         break;
      case TatangaState_Jump:
         break;
   }
}

//------------------------------------------------------------------------------

// Update Tatanga state at each frame
void Tatanga::Update()
{
   // Update Tatanga depending on the current state
   switch (m_state)
   {
      //========================================================================c
      case TatangaState_Idle:
      case TatangaState_Run:

         // Move left / right
         MoveOnGround();

         // ----------------
         // Update animation
         // ----------------
         if (m_speedRun == 0.0)
         {
            if (m_state != TatangaState_Idle)
            {
               START_ANIM_IDLE;
               m_state = TatangaState_Idle;
            }
         }
         else
         {
            if (m_state != TatangaState_Run)
            {
               START_ANIM_RUN;
               m_state = TatangaState_Run;
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
      case TatangaState_Strike:

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
               m_state = TatangaState_Jump;
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
      case TatangaState_Jump:

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
               m_state = TatangaState_Idle;
            }
            else
            {
               m_flip = m_speedRun > 0.0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
               START_ANIM_RUN;
               m_state = TatangaState_Run;
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

// Move Tatanga with left / right buttons
void Tatanga::MoveOnGround()
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

// Move Tatanga in space
Planet *Tatanga::MoveInSpace()
{
   // ---------------------------
   // Update acceleration & speed
   // ---------------------------
   double tatangaCenterX = m_x + (m_width / 2.0);
   double tatangaCenterY = m_y + (m_height / 2.0);
   double distanceTatangaPlanet = 0.0;
   for (std::vector<Planet*>::iterator planetIt = g_planets.begin(); planetIt != g_planets.end(); ++planetIt)
   {
      distanceTatangaPlanet = sqrt(pow(tatangaCenterX - (*planetIt)->m_centerX, 2) + pow(tatangaCenterY - (*planetIt)->m_centerY, 2));
      if (distanceTatangaPlanet < (*planetIt)->m_radius + GAP_SPRITE_CENTER_GROUND)
      {
         // Angle of rotation at contact
         m_angle = atan((tatangaCenterY - (*planetIt)->m_centerY) / (tatangaCenterX - (*planetIt)->m_centerX));
         if (tatangaCenterX < (*planetIt)->m_centerX)
            m_angle += M_PI;
         // Run speed at contact
         m_speedRun = (m_speedX * sin(-m_angle) + m_speedY * cos(-m_angle)) * 0.7;
         if (m_speedRun > RUN_SPEED_MAX)
            m_speedRun = RUN_SPEED_MAX;
         else if (m_speedRun < -RUN_SPEED_MAX)
            m_speedRun = -RUN_SPEED_MAX;
         return *planetIt;
      }
      m_accelX = ((*planetIt)->m_centerX - tatangaCenterX) * (*planetIt)->m_mass / pow(distanceTatangaPlanet, 2);
      m_accelY = ((*planetIt)->m_centerY - tatangaCenterY) * (*planetIt)->m_mass / pow(distanceTatangaPlanet, 2);
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
