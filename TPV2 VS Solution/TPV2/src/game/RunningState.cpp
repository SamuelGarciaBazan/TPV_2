#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

RunningState::RunningState()
{
		
}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	//if 0 asteroids, set gameOverState

	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		//go pause state
	}

	//update de entidades


	//collisions

	//render de todo

	//refresh del manager

	//a�adir un asteroide cada 5 segundos

}

void RunningState::enter()
{
}

void RunningState::leave()
{
}
