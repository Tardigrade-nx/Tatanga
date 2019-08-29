#ifndef _TATANGA_H_
#define _TATANGA_H_

#include <string>
#include <SDL2/SDL.h>
#include "sprite.h"

class Planet;

typedef enum
{
   TatangaState_Idle = 0,
   TatangaState_Run,
   TatangaState_Strike,
   TatangaState_Jump
}
TatangaState;

//------------------------------------------------------------------------------

class Tatanga: public Sprite
{

   public:

   // Constructor
   Tatanga(const std::string &p_textureFile, int p_width, int p_height, Planet *p_planet);

   // Destructor
   virtual ~Tatanga();

   // Handle events
   virtual void Handle(const SDL_Event &p_event);

   // Update Tatanga state at each frame
   virtual void Update();

   // Reset Tatanga on a new planet
   void Reset(Planet *p_planet);

//------------------------------------------------------------------------------

   public:

   // Tatanga's state
   TatangaState m_state;

   // Speed and acceleration when running on ground
   double m_accelRun;
   double m_speedRun;

   // Speed and acceleration when floating in space
   double m_accelX;
   double m_accelY;
   double m_speedX;
   double m_speedY;

   // Planet where Tatanga is walking on
   Planet *m_planet;

   // Rotation speed when floating, in radians
   double m_rotationSpeed;

//------------------------------------------------------------------------------

   private:

   // Move Tatanga with left / right buttons
   void MoveOnGround();

   // Move Tatanga in space
   // Returns Planet if there's a collision
   Planet *MoveInSpace();

   // Forbidden
   Tatanga();
   Tatanga(const Tatanga&);
   const Tatanga& operator=(const Tatanga&);

//------------------------------------------------------------------------------
};

#endif
