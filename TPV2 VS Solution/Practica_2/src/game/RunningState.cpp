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
#include "../systems/ScoreSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem*gh, FoodSystem*fo,
	ImmunitySystem*im, CollisionsSystem*col, RenderSystem*r,ScoreSystem* sc)
	:pacManSystem(pc),ghostSystem(gh),foodSystem(fo),
	immunitySystem(im),collisionsSystem(col),renderSystem(r),scoreSystem(sc)
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

		mngr->send(m,true);
	}
	if (ih().isKeyDown(SDL_SCANCODE_L)) {

		Message m;
		m.id = _m_IMMUNITY_END;

		mngr->send(m,true);
	}

	SDL_Rect destinyRect{ 0,0,sdlutils().width(),sdlutils().height() };

	sdlutils().images().at("playBackground").render(destinyRect);
	
	pacManSystem->update();
	ghostSystem->update();
	foodSystem->update();
	immunitySystem->update();
	collisionsSystem->update();
	renderSystem->update();
	scoreSystem->update();
}





void RunningState::enter()
{
	//reset de timers
	
}

void RunningState::leave()
{
}








