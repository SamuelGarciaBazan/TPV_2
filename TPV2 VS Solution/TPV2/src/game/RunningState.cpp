#include "RunningState.h"
#include "../sdlutils/InputHandler.h"

#include "FighterFacade.h"
#include "AsteroidsFacade.h"
#include "MissilesFacade.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../components/Health.h"

#include "../utils/Collisions.h"

#include <vector>

RunningState::RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids, MissilesFacade* missiles)
	:fighter(fighter),asteorids(asteorids),missiles(missiles)
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

		//colision asteroides con agujeros negros

		auto blackHolesList = mngr->getEntities(ecs::grp::BLACKHOLES);

		auto blackHolesIndex = 0;

		bool colision = false;

		while (blackHolesIndex < blackHolesList.size() && !colision) {

			//blackHolesTransform
			auto bhT = mngr->getComponent<Transform>(blackHolesList[blackHolesIndex]);

			if (Collisions::collidesWithRotation(
				bhT->getPos(), bhT->getWidth(), bhT->getHeight(), bhT->getRot(),
				aT->getPos(), aT->getWidth(), aT->getHeight(), aT->getRot())) {

				colision = true;

				int x = sdlutils().rand().nextInt(0, sdlutils().width());
				int y = sdlutils().rand().nextInt(0, sdlutils().height());

				aT->getPos().set(x, y);

			}
			++blackHolesIndex;
		}




		i++;
	}

	//colisions black holes
	#pragma region BlackHolesCollisions



	auto blackHolesList = mngr->getEntities(ecs::grp::BLACKHOLES);

	i = 0;

	while (i < blackHolesList.size() && !changeState) {

		//black hole transform
		auto bhT = mngr->getComponent<Transform>(blackHolesList[i]);

		//colision con el fighter
		if (Collisions::collidesWithRotation(
			ft->getPos(), ft->getWidth(), ft->getHeight(), ft->getRot(),
			bhT->getPos(), bhT->getWidth(), bhT->getHeight(), bhT->getRot())) {


			auto health = mngr->getComponent<Health>(fighter);
			health->decreaseLifes();


			if (health->getCurrentLifes() == 0) {
				Game::instance()->setState(Game::GAMEOVER);
			}
			else {
				
				Game::instance()->setState(Game::NEWROUND);
			}

			changeState = true;
		}

		i++;
	}

#pragma endregion

	
	#pragma region Missiles collision



	auto misilesList = mngr->getEntities(ecs::grp::MISSILES);

	auto misilesIndex = 0;

	while (misilesIndex < misilesList.size() && !changeState) {

		//misilTransform
		auto mT = mngr->getComponent<Transform>(misilesList[misilesIndex]);

		//colision con el fighter
		if (Collisions::collidesWithRotation(
			ft->getPos(), ft->getWidth(), ft->getHeight(), ft->getRot(),
			mT->getPos(), mT->getWidth(), mT->getHeight(), mT->getRot())) {


			auto health = mngr->getComponent<Health>(fighter);
			health->decreaseLifes();

			if (health->getCurrentLifes() == 0) {
				Game::instance()->setState(Game::GAMEOVER);
			}
			else {
				Game::instance()->setState(Game::NEWROUND);
			}

			changeState = true;
		}


		auto it = mngr->getComponent<Gun>(fighter)->begin();


		//colision balas con misiles
		while (it != mngr->getComponent<Gun>(fighter)->end()) {

			if ((*it).used) {

				if (Collisions::collidesWithRotation(
					(*it).pos, (*it).width, (*it).height, (*it).rot,
					mT->getPos(), mT->getWidth(), mT->getHeight(), mT->getRot())) {

					//desmarcar la bala
					(*it).used = false;

					mngr->setAlive(misilesList[misilesIndex],false);

				}
			}
			++it;
		}


		//si sale de la pantalla se destruye
		if (mT->getPos().getX() < 0 || mT->getPos().getX() > sdlutils().width() ||
			mT->getPos().getY() < 0 || mT->getPos().getY() > sdlutils().height()) {
			mngr->setAlive(misilesList[misilesIndex], false);
		}



		misilesIndex++;
	}

#pragma endregion


	//render de todo

	mngr->render();

	//refresh del manager
	mngr->refresh();

	//añadir un asteroide cada 5 segundos

	if ((lastGeneration + asteroidSpawnRate) < sdlutils().virtualTimer().currTime()) {
		lastGeneration = sdlutils().virtualTimer().currTime();
		asteorids->create_asteroids(1);
	}

	//añadir un mision cada 15 segundos
	if ((lastMissile + missileSpawnRate) < sdlutils().virtualTimer().currTime()) {
		lastMissile = sdlutils().virtualTimer().currTime();
		missiles->createMisile();
	}
}

void RunningState::enter()
{
	//reset del timer
	lastGeneration = sdlutils().virtualTimer().currTime();
	lastMissile = sdlutils().virtualTimer().currTime();
}

void RunningState::leave()
{
}
