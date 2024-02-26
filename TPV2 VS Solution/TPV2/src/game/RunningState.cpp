#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

#include "FighterFacade.h"
#include "AsteroidsFacade.h"

RunningState::RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids)
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

	//añadir un asteroide cada 5 segundos

}

void RunningState::enter()
{
}

void RunningState::leave()
{
}
