#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "def.h"

typedef enum
{
   SpriteState_Idle = 0,
   SpriteState_Run,
   SpriteState_Strike,
   SpriteState_Jump
}
SpriteState;

//------------------------------------------------------------------------------

class Sprite
{

   public:

   // Constructor
   Sprite(const std::string &p_textureFile, int p_width, int p_height, Planet *p_planet);

   // Destructor
   virtual ~Sprite();

   // Handle events
   void Handle(const SDL_Event &p_event);

   // Update sprite state at each frame
   void Update();

   // Render sprite
   void Render();

   // Set x and y coordinates
   void SetPosition(const double &p_x, const double &p_y);

//------------------------------------------------------------------------------

   public:

   // Texture containing the sprite sheet
   SDL_Texture *m_texture;

   // Sprite state
   SpriteState m_state;

   // Coordinates of the sprite
   double m_x;
   double m_y;

   // Width and height of a sprite frame
   int m_width;
   int m_height;

   // Speed and acceleration
   double m_accelX;
   double m_accelY;
   double m_speedX;
   double m_speedY;

   // Planet where the sprite is walking on
   Planet *m_planet;

   // Angle of the sprite on the planet, in radians
   double m_angle;

   // Rotation speed when floating, in radians
   double m_rotationSpeed;

   // Animation id (ie. row)
   int m_animId;

   // Animation step (ie. column)
   int m_animStep;

   // Number of animation steps
   int m_animNbSteps;

   // Animation speed (in frames)
   int m_animSpeed;

   // Frame counter for animations
   int m_frameCounter;

   // Sprite flip mode
   SDL_RendererFlip m_flip;

//------------------------------------------------------------------------------

   private:

   // Start animation
   void StartAnim(int p_animId, int p_nbSteps, int p_speed);

   // Move sprite with left / right buttons
   void MoveOnGround();

   // Move sprite in space
   // Returns Planet if there's a collision
   Planet *MoveInSpace();

   // Forbidden
   Sprite();
   Sprite(const Sprite&);
   const Sprite& operator=(const Sprite&);

//------------------------------------------------------------------------------
};

#endif
