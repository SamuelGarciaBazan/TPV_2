#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

#include "FighterFacade.h"
#include "AsteroidsFacade.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../components/Health.h"

#include "../utils/Collisions.h"

#include <vector>

RunningState::RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids) 
	:fighter(fighter),asteorids(asteorids)
{
		
}

RunningState::~RunningState()
{
}

void RunningState::update()
{

	auto mngr = Game::instance()->getMngr();

	//if 0 asteroids, set gameOverState
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);

	}

	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		//go pause state
		Game::instance()->setState(Game::PAUSED);

	}

	//update de entidades
	mngr->update();

	//collisions
	
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);

	//fighter transform
	auto ft = mngr->getComponent<Transform>(fighter);
	
	//vector de asteroids
	auto _asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);

	//recorrer los asteroides
	int i = 0;
	bool changeState = false;

	while(i < _asteroids.size() && !changeState){

		//asteroid transform
		auto aT = mngr->getComponent<Transform>(_asteroids[i]);

		//bullet it
		auto it = mngr->getComponent<Gun>(fighter)->begin();

		//colision con el fighter
		if (Collisions::collidesWithRotation(
			ft->getPos(), ft->getWidth(), ft->getHeight(), ft->getRot(),
			aT->getPos(), aT->getWidth(), aT->getHeight(), aT->getRot())) {


			auto health = mngr->getComponent<Health>(fighter);
			health->decreaseLifes();


			if (health->getCurrentLifes() == 0) {
				Game::instance()->setState(Game::GAMEOVER);

			}
			else {
				//reset del timer
				lastGeneration = sdlutils().virtualTimer().currTime();
				Game::instance()->setState(Game::NEWROUND);
			}

			changeState = true;
		}

		//colision balas con asteroides
		while (it != mngr->getComponent<Gun>(fighter)->end()) {

			if ((*it).used) {

				if (Collisions::collidesWithRotation(
						(*it).pos, (*it).width, (*it).height, (*it).rot,
						aT->getPos(), aT->getWidth(), aT->getHeight(), aT->getRot())) {

					//desmarcar la bala
					(*it).used = false;
					
					mngr->setAlive(_asteroids[i], false);

					asteorids->split_astroid(_asteroids[i]);
				}
			}
			++it;
		}

		i++;
	}



	//render de todo

	mngr->render();

	//refresh del manager
	mngr->refresh();

	//añadir un asteroide cada 5 segundos

	if ((lastGeneration + asteroidSpawnRate) < sdlutils().virtualTimer().currTime()) {
		lastGeneration = sdlutils().virtualTimer().currTime();
		asteorids->create_asteroids(1);
	}
}

void RunningState::enter()
{

}

void RunningState::leave()
{
}
