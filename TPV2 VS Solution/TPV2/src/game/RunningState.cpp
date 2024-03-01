#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

#include "FighterFacade.h"
#include "AsteroidsFacade.h"

#include "Game.h"
#include "../ecs/Manager.h"



RunningState::RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids)
{
		
}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	//if 0 asteroids, set gameOverState

	if (Game::instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		std::cout << "GAMEOVERSTATE" << std::endl;
	}

	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		//go pause state
		Game::instance()->setState(Game::PAUSED);

	}

	//update de entidades
	Game::instance()->getMngr()->update();

	//collisions

	//render de todo

	Game::instance()->getMngr()->render();

	//refresh del manager

	//añadir un asteroide cada 5 segundos

}

void RunningState::enter()
{
}

void RunningState::leave()
{
}
