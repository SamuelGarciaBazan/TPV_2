#include "AsteroidsUtils.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../ecs/ecs.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/ImageWithFrames.h"
#include "../components/Generations.h"


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
	mngr->addComponent<Transform>(ast, Vector2D(100,100), Vector2D(0,0), 50.f,40.f, 30.f);
	//imageWithFrames
	mngr->addComponent<ImageWithFrames>(ast, "asteroid",5,6);
	//ShowAtOppostiteSide
	mngr->addComponent<ShowAtOpposieSide>(ast);
	//Generations
	mngr->addComponent<Generations>(ast,3);
	//Follow

	//TowardDestination




}
