#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "def.h"

#define RUN_SPEED_MAX      5.0
#define RUN_ACCELERATION   0.1
#define RUN_DECELERATION   0.1

//------------------------------------------------------------------------------

class Sprite
{

   public:

   // Constructor
   Sprite(const std::string &p_textureFile, int p_width, int p_height);

   // Destructor
   virtual ~Sprite();

   // Update sprite state at each frame
   void Update();

   // Render sprite
   void Render();

   // Start animation
   void StartAnim(int p_animId, int p_nbSteps, int p_speed);

   // Set x and y coordinates
   void SetPosition(const double &p_x, const double &p_y);

//------------------------------------------------------------------------------

   public:

   // Texture containing the sprite sheet
   SDL_Texture *m_texture;

   // Coordinates of the sprite
   double m_x;
   double m_y;

   // Width and height of a sprite frame
   int m_width;
   int m_height;

   // Speed and acceleration for running
   double m_runAccel;
   double m_runSpeed;

   // Planet where the sprite is walking on
   Planet *m_planet;

   // Angle of the sprite on the planet, in radians
   double m_angle;

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

   // Forbidden
   Sprite();
   Sprite(const Sprite&);
   const Sprite& operator=(const Sprite&);

//------------------------------------------------------------------------------
};

#endif
