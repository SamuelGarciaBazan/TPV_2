#include "AsteroidsUtils.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../ecs/ecs.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/Image.h"


void AsteroidsUtils::create_asteroids(int n)
{
	for (int i = 0; i < n; i++) {
		create_asteroid();
	}
}

void AsteroidsUtils::remove_all_asteroids()
{
}

void AsteroidsUtils::split_astroid(ecs::Entity* a)
{
}

void AsteroidsUtils::create_asteroid()
{
	auto mngr = Game::instance()->getMngr();

	auto ast = mngr->addEntity(ecs::grp::ASTEROIDS);

	//transform
	mngr->addComponent<Transform>(ast);
	//imageWithFrames
	//mngr->addComponent<Image>(ast, "asteroid");

	//ShowAtOppostiteSide
	mngr->addComponent<ShowAtOpposieSide>(ast);
	//Generations

	//Follow

	//TowardDestination




}
