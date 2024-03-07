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
		create_asteroid();
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
	//int r = sdlutils().rand().nextInt(0, 360);
	//Vector2D pos = p + v.rotate(r) * 2 * std::max(w, h).
	//Vector2D vel = v.rotate(r) * 1.1f
}

void AsteroidsUtils::create_asteroid()
{
	auto mngr = Game::instance()->getMngr();

	auto ast = mngr->addEntity(ecs::grp::ASTEROIDS);


	//size of centerZone
	int centerZone = 100;

	//posicion de inicio del asteroide
	Vector2D pos(sdlutils().rand().nextInt(0, sdlutils().width()),
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

	//posicon del centro de la pantalla
	Vector2D cPos(sdlutils().width() / 2 + sdlutils().rand().nextInt(0, centerZone),
		sdlutils().height() / 2 + sdlutils().rand().nextInt(0, centerZone));

	//velocidad del asteroide aleatoria (entre 0,1)
	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
	Vector2D velVector = (cPos - pos).normalize() * speed;

	//rotacion aleatoria
	float rotation = sdlutils().rand().nextInt(0, 3600) / 10.0f;

	//numero de generaciones aleatoria
	int nGens = sdlutils().rand().nextInt(1, 4);

	//tamanos aleatorios(en cierto margen)
	float sizeX = sdlutils().rand().nextInt(8, 13) + (5.0) * nGens;
	float sizeY = sdlutils().rand().nextInt(8, 13) + (5.0) * nGens;

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
	mngr->addComponent<Generations>(ast,3);

	

	if (follow) {
		//Follow
		mngr->addComponent<Follow>(ast,& mngr->getComponent<Transform>(mngr->getHandler(ecs::hdlr::FIGHTER))->getPos());
	}
	else{
		//TowardDestination
		mngr->addComponent<TowardDestination>(ast);
	}
	
	

}
