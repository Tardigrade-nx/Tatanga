#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <SDL2/SDL.h>

//------------------------------------------------------------------------------

class Sprite
{

   public:

   // Constructor
   Sprite(const std::string &p_textureFile, int p_width, int p_height);

   // Destructor
   virtual ~Sprite();

   // Handle events
   virtual void Handle(const SDL_Event &p_event);

   // Update sprite state at each frame
   virtual void Update();

   // Render sprite
   virtual void Render();

   // Set x and y coordinates
   void SetPosition(const double &p_x, const double &p_y);

   // Start animation
   void StartAnim(int p_animId, int p_nbSteps, int p_speed);

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

   // Rotation angle of sprite, in radians, trigonometry coordinates (vertical = -PI/2)
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
