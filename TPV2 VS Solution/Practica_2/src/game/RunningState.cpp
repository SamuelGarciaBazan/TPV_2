#include "RunningState.h"
#include "../sdlutils/InputHandler.h"


#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Health.h"

#include "../utils/Collisions.h"

#include <vector>


#include "../systems/PacManSystem.h"

RunningState::RunningState(PacManSystem* pacManSystem)
	:pacManSystem(pacManSystem)
{

}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	auto mngr = Game::instance()->getMngr();


	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		//go pause state
		Game::instance()->setState(Game::PAUSED);
	}

	//update de entidades
	mngr->update();

	//colision
	collisions();

	//render de todo
	mngr->render();

	//refresh del manager
	mngr->refresh();

	
	pacManSystem->update();
}





void RunningState::enter()
{
	//reset de timers
	
}

void RunningState::leave()
{
}




void RunningState::collisions()
{
	
	

}


bool RunningState::collidesWithRotation(Transform* t1, Transform* t2)
{
	return Collisions::collidesWithRotation(
		t1->getPos(), t1->getWidth(), t1->getHeight(), t1->getRot(),
		t2->getPos(), t2->getWidth(), t2->getHeight(), t2->getRot());
}



