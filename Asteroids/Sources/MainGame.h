#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "Frog.h"
#include "MenuState.h"

namespace Webfoot {

class Ball;
class Ship;
//==============================================================================

class MainGame : public MenuState
{
public:
   typedef MenuState Inherited;

   MainGame();
   virtual ~MainGame() {};
   
   virtual void Init();
   virtual void Deinit();

   /// Call this on every frame to update the positions.
   virtual void Update();
   /// Call this on every frame to draw the images.
   virtual void Draw();

   static MainGame instance;

protected:
   /// Returns the name of the GUI layer
   virtual const char* GUILayerNameGet();

   /// The ball that bounces around the screen.
   Ball* ball;
};

MainGame* const theMainGame = &MainGame::instance;

//==============================================================================
class Ship
{
private: 
	Sprite *mysprite;

public: 
	Point2F position; 
	Point2F velocity; 
	Point2F thrust_velocity; 
	Point2F friction; 
	float rotation;

	Ship();
	~Ship() {};
	void Init();
	void DeInit();
	void Draw(); 
	void Update(unsigned int dt); 
	void ProcessInput(unsigned int input); 
};

//==============================================================================

/// A bouncing ball
class Ball
{
public:
   Ball();
   
   /// Initialize the ball
   void Init();
   /// Clean up the ball
   void Deinit();

   /// Make any changes for the given frame.  'dt' is the amount of time that
   /// has passed since the last frame, in milliseconds.
   void Update(unsigned int dt);
   /// Draw the ball.
   void Draw();

protected:
   /// Appearance of the ball.
   Image* image;
   /// Current position of the ball.
   Point2F position;
   /// Current velocity of the ball.
   Point2F velocity;
};

//==============================================================================

} //namespace Webfoot {

#endif //#ifndef __MAINGAME_H__
