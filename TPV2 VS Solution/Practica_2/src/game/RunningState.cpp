#include "RunningState.h"
#include "../sdlutils/InputHandler.h"


#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Health.h"

#include "../utils/Collisions.h"

#include <vector>


#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/RenderSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem*gh, FoodSystem*fo,
	ImmunitySystem*im, CollisionsSystem*col, RenderSystem*r)
	:pacManSystem(pc),ghostSystem(gh),foodSystem(fo),
	immunitySystem(im),collisionsSystem(col),renderSystem(r)
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


	//PARA TESTEAR
	if (ih().isKeyDown(SDL_SCANCODE_K)) {


		Message m;
		m.id = _m_IMMUNITY_START;

		mngr->send(m);
	}
	if (ih().isKeyDown(SDL_SCANCODE_L)) {

		Message m;
		m.id = _m_IMMUNITY_END;

		mngr->send(m);
	}

	/*antiguo update
	//update de entidades
	mngr->update();

	//colision
	collisions();

	//render de todo
	mngr->render();

	//refresh del manager
	mngr->refresh();
	*/

	
	pacManSystem->update();
	ghostSystem->update();
	foodSystem->update();
	immunitySystem->update();
	collisionsSystem->update();
	renderSystem->update();
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



