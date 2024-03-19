#include "AsteroidsUtils.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../ecs/ecs.h"

#include "../sdlutils/SDLUtils.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/ImageWithFrames.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/TowardDestination.h"


void AsteroidsUtils::create_asteroids(int n)
{
	for (int i = 0; i < n; i++) {

		Vector2D pos;

		bool generateInborders = true;

		//size of centerZone
		int centerZone = 100;


		//otro metodo de generacion
		if (!generateInborders) {

			//posicion de inicio del asteroide
			pos = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()),
				sdlutils().rand().nextInt(0, sdlutils().height()));


			//Colocacion del asteroide fuera del centro

			//si la X esta en la center zone
			if (pos.getX() >= (sdlutils().width() / 2) - centerZone &&
				pos.getX() <= (sdlutils().width() / 2) + centerZone) {

				pos.setX(pos.getX() + sdlutils().rand().nextInt(0, (sdlutils().width() - (2 * centerZone))));
			}

			//si la Y esta en la center zone
			if (pos.getY() >= (sdlutils().height() / 2) - centerZone &&
				pos.getY() <= (sdlutils().height() / 2) + centerZone) {

				pos.setY(pos.getY() + sdlutils().rand().nextInt(0, (sdlutils().height() - (2 * centerZone))));
			}

		}
		else {
			int border = sdlutils().rand().nextInt(0, 4);

			/*
			    1
			0       2
			    3
			*/

			switch (border)
			{
				case 0:
					pos = Vector2D(0, sdlutils().rand().nextInt(0, sdlutils().height()));
					break;
				case 1:
					pos = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()),0);

					break;
				case 2:
					pos = Vector2D(sdlutils().width(), sdlutils().rand().nextInt(0, sdlutils().height()));
					break;
				case 3:
					pos = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().height());
					break;
				default:
					break;
			}

		}

		//posicon del centro de la pantalla
		Vector2D cPos(sdlutils().width() / 2 + sdlutils().rand().nextInt(0, centerZone),
			sdlutils().height() / 2 + sdlutils().rand().nextInt(0, centerZone));

		//velocidad del asteroide aleatoria (entre 0,1)
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D velVector = (cPos - pos).normalize() * speed;

		//numero de generaciones aleatoria
		int nGens = sdlutils().rand().nextInt(0, 3);



		create_asteroid(pos,velVector,nGens);
	}
}

void AsteroidsUtils::remove_all_asteroids()
{
	auto mngr = Game::instance()->getMngr();
	for (auto& e : mngr->getEntities(ecs::grp::ASTEROIDS)) {
		mngr->setAlive(e, false);
	}

	mngr->refresh();
}

void AsteroidsUtils::split_astroid(ecs::Entity* a)
{
	auto mngr = Game::instance()->getMngr();
	
	auto genComponent = mngr->getComponent<Generations>(a);

	if (genComponent->getGenerations() > 0) {

		auto astTransform = mngr->getComponent<Transform>(a);


		Vector2D p = astTransform->getPos();
		Vector2D v = astTransform->getVel();

		int r = sdlutils().rand().nextInt(0, 360);
	
		int w = 10;

		Vector2D pos = p + v.rotate(r) * 2 * w;
		Vector2D vel = v.rotate(r) * 1.1f;

		create_asteroid(pos, vel, genComponent->getGenerations() - 1);

		r = sdlutils().rand().nextInt(0, 360);
		pos = p + v.rotate(r) * 2 * w;

		create_asteroid(pos, vel, genComponent->getGenerations() - 1);

	 vel = v.rotate(r) * 1.1f;
	}

	mngr->setAlive(a, false);
}

void AsteroidsUtils::create_asteroid(Vector2D pos, Vector2D velVector, int nGens)
{
	auto mngr = Game::instance()->getMngr();

	auto ast = mngr->addEntity(ecs::grp::ASTEROIDS);

	//rotacion aleatoria
	float rotation = sdlutils().rand().nextInt(0, 3600) / 10.0f;

	//tamanos aleatorios(en cierto margen)
	float sizeX = sdlutils().rand().nextInt(19, 23) + (4.0) * nGens;
	float sizeY = sdlutils().rand().nextInt(19, 23) + (4.0) * nGens;

	//transform
	mngr->addComponent<Transform>(ast, pos, velVector, sizeX,sizeY, rotation);
	//imageWithFrames
	int nFils = 5;
	int nCols = 6;

	bool follow = sdlutils().rand().nextInt(0, 2) == 0;

	mngr->addComponent<ImageWithFrames>(ast, follow ? "asteroid_gold" : "asteroid", nFils, nCols);
	//ShowAtOppostiteSide
	mngr->addComponent<ShowAtOpposieSide>(ast);
	//Generations
	mngr->addComponent<Generations>(ast,nGens);

	

	if (follow) {
		//Follow
		mngr->addComponent<Follow>(ast,& mngr->getComponent<Transform>(mngr->getHandler(ecs::hdlr::FIGHTER))->getPos());
	}
	else{
		//TowardDestination
		mngr->addComponent<TowardDestination>(ast);
	}
	
	

}
