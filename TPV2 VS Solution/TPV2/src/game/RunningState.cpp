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

	//colision
	collisions();

	//render de todo
	mngr->render();

	//refresh del manager
	mngr->refresh();

	spawnAsteroids();
	spawnMissiles();

}





void RunningState::enter()
{
	//reset de timers
	lastGeneration = sdlutils().virtualTimer().currTime();
	lastMissile = sdlutils().virtualTimer().currTime();
}

void RunningState::leave()
{
}


void RunningState::spawnAsteroids()
{
	//añadir un asteroide cada 5 segundos

	if ((lastGeneration + asteroidSpawnRate) < sdlutils().virtualTimer().currTime()) {
		lastGeneration = sdlutils().virtualTimer().currTime();
		asteorids->create_asteroids(1);
	}
}

void RunningState::spawnMissiles()
{
	//añadir un mision cada 15 segundos
	if ((lastMissile + missileSpawnRate) < sdlutils().virtualTimer().currTime()) {
		lastMissile = sdlutils().virtualTimer().currTime();
		missiles->createMisile();
	}
}

void RunningState::collisions()
{
	
	collisionsAsteroids();
	//colisions black holes
	collisionsBlackHolesFigher();

	collisionsMissiles();

}

void RunningState::collisionsAsteroids()
{
	auto mngr = Game::instance()->getMngr();


	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);

	//fighter transform
	auto ft = mngr->getComponent<Transform>(fighter);

	//vector de asteroids
	auto _asteroidsList = mngr->getEntities(ecs::grp::ASTEROIDS);

	//recorrer los asteroides
	int i = 0;
	bool changeState = false;

	while (i < _asteroidsList.size() && !changeState) {

		//asteroid transform
		auto aT = mngr->getComponent<Transform>(_asteroidsList[i]);

		//colision con el fighter	
		if (collidesWithRotation(ft, aT)) {

			fighterDeath();
			changeState = true;
		}

		//bullet it
		auto it = mngr->getComponent<Gun>(fighter)->begin();

		//colision balas con asteroides
		while (it != mngr->getComponent<Gun>(fighter)->end()) {

			if ((*it).used) {

				if (Collisions::collidesWithRotation(
					(*it).pos, (*it).width, (*it).height, (*it).rot,
					aT->getPos(), aT->getWidth(), aT->getHeight(), aT->getRot())) {

					//desmarcar la bala
					(*it).used = false;

					mngr->setAlive(_asteroidsList[i], false);

					asteorids->split_astroid(_asteroidsList[i]);
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

			if (collidesWithRotation(bhT, aT)) {

				colision = true;

				//colocar en una posicion aleatoria
				int x = sdlutils().rand().nextInt(0, sdlutils().width());
				int y = sdlutils().rand().nextInt(0, sdlutils().height());

				aT->getPos().set(x, y);

			}
			++blackHolesIndex;
		}

		i++;
	}
}

void RunningState::collisionsBlackHolesFigher()
{

	auto mngr = Game::instance()->getMngr();

	auto blackHolesList = mngr->getEntities(ecs::grp::BLACKHOLES);

	auto ft = mngr->getComponent<Transform>(mngr->getHandler(ecs::hdlr::FIGHTER));

	int i = 0;
	bool changeState = false;

	while (i < blackHolesList.size() && !changeState) {

		//black hole transform
		auto bhT = mngr->getComponent<Transform>(blackHolesList[i]);

		//colision con el fighter	
		if (collidesWithRotation(ft, bhT)) {

			fighterDeath();
			changeState = true;
		}

		i++;
	}
}

void RunningState::collisionsMissiles()
{
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto ft = mngr->getComponent<Transform>(mngr->getHandler(ecs::hdlr::FIGHTER));




	auto misilesList = mngr->getEntities(ecs::grp::MISSILES);

	auto misilesIndex = 0;
	bool changeState = false;


	while (misilesIndex < misilesList.size() && !changeState) {

		//misilTransform
		auto mT = mngr->getComponent<Transform>(misilesList[misilesIndex]);

		//colision con el fighter

		if (collidesWithRotation(ft, mT)) {
			fighterDeath();
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

					mngr->setAlive(misilesList[misilesIndex], false);

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
}

bool RunningState::collidesWithRotation(Transform* t1, Transform* t2)
{
	return Collisions::collidesWithRotation(
		t1->getPos(), t1->getWidth(), t1->getHeight(), t1->getRot(),
		t2->getPos(), t2->getWidth(), t2->getHeight(), t2->getRot());
}



void RunningState::fighterDeath()
{
	sdlutils().soundEffects().at("explosion").play();
	auto mngr = Game::instance()->getMngr();
	
	if (fighter->update_lives(-1) == 0) {
		Game::instance()->setState(Game::GAMEOVER);
	}
	else {
		Game::instance()->setState(Game::NEWROUND);
	}
}
