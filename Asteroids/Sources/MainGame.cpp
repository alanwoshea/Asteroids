#include "Frog.h"
#include "MainGame.h"
#include "MainUpdate.h"

using namespace Webfoot;

/// Speed of the ball along a given axis in pixels per second.
#define BALL_AXIS_SPEED 400.0f

MainGame MainGame::instance;

//==============================================================================

/// Main GUI
#define GUI_LAYER_NAME "MainGame"

//-----------------------------------------------------------------------------

MainGame::MainGame()
{
   ball = NULL;
}

//-----------------------------------------------------------------------------

void MainGame::Init()
{
   Inherited::Init();

   // Create and initialize the ball.
   ball = frog_new Ball();
   ball->Init();
}

//-----------------------------------------------------------------------------

void MainGame::Deinit()
{
   // Deinitialize and delete the ball.
   if(ball)
   {
      ball->Deinit();
      frog_delete ball;
      ball = NULL;
   }
   
   Inherited::Deinit();
}

//-----------------------------------------------------------------------------

const char* MainGame::GUILayerNameGet()
{
   return GUI_LAYER_NAME;
}

//-----------------------------------------------------------------------------

void MainGame::Update()
{
   Inherited::Update();

   unsigned int dt = theClock->LoopDurationGet();

   ball->Update(dt);

   // Return to the previous menu if the escape key is pressed.
   if(!theStates->StateChangeCheck() && theKeyboard->KeyJustPressed(KEY_ESCAPE))
   {
      theMainGame->StateChangeTransitionBegin(true);
      theStates->Pop();
   }
}

//-----------------------------------------------------------------------------

void MainGame::Draw()
{
   ball->Draw();
}

//==============================================================================

Ball::Ball()
{
   // Initialize pointers to NULL for safety.
   image = NULL;
}

//------------------------------------------------------------------------------

void Ball::Init()
{
   // Load the image of the ball.
   image = theImages->Load("Ball");

   // Start the ball in the middle of the screen.
   position = Point2F::Create(theScreen->SizeGet() / 2);

   // The ball will initially be moving down and to the right.
   velocity.Set(BALL_AXIS_SPEED, BALL_AXIS_SPEED);
}

//------------------------------------------------------------------------------

void Ball::Deinit()
{
   // Unload the image of the ball.
   if(image)
   {
      theImages->Unload(image);
      image = NULL;
   }
}

//------------------------------------------------------------------------------

void Ball::Update(unsigned int dt)
{
   // Get a floating point number for the duration of the last frame in seconds.
   float dtSeconds = (float)dt / 1000.0f;

   // Update the position of the ball.
   position += velocity * dtSeconds;

   // The position of the ball corresponds to its center.  We want to keep the
   // whole ball on-screen, so figure out the area within which the center must
   // stay.
   Point2F ballSize = Point2F::Create(image->SizeGet());
   Point2F halfBallSize = ballSize / 2.0f;
   Box2F ballArea = {halfBallSize.x, halfBallSize.y,
      (float)theScreen->WidthGet() - ballSize.x,
      (float)theScreen->HeightGet() - ballSize.y};

   // If the ball has gone too far in any direction, make sure its velocity
   // will bring it back.

   // See if it's too far right.
   if((position.x > ballArea.MaxXGet()) && (velocity.x > 0.0f))
      velocity.x *= -1.0f;

   // See if it's too far left.
   if((position.x < ballArea.x) && (velocity.x < 0.0f))
      velocity.x *= -1.0f;

   // See if it's too far down.
   if((position.y > ballArea.MaxYGet()) && (velocity.y > 0.0f))
      velocity.y *= -1.0f;

   // See if it's too far up.
   if((position.y < ballArea.y) && (velocity.y < 0.0f))
      velocity.y *= -1.0f;
}

//------------------------------------------------------------------------------

void Ball::Draw()
{
   // The center of the ball is in the center of the image, so use an offset.
   image->Draw(position - (Point2F::Create(image->SizeGet()) / 2.0f));
}

//------------------------------------------------------------------------------
