#include "MissileUtils.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Follow.h"
#include "../components/LookAt.h"



MissileUtils::MissileUtils()
{
}

MissileUtils::~MissileUtils()
{
}

void MissileUtils::remove_all_missiles()
{

	auto mngr = Game::instance()->getMngr();
	for (auto& e : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(e, false);
	}

	mngr->refresh();
}

void MissileUtils::createMisile()
{
	auto mngr = Game::instance()->getMngr();

	int corner = sdlutils().rand().nextInt(0, 4);

	/*
	0   1

	2   3
	
	*/

	int x = corner == 0 || corner == 2 ? 0 : sdlutils().width();
	int y = corner == 0 || corner == 1 ? 0 : sdlutils().height();

	Vector2D pos(x, y);
	Vector2D vel;

	auto fTransform = mngr->getComponent<Transform>(mngr->getHandler(ecs::hdlr::FIGHTER));

	float velMagnitude = sdlutils().rand().nextInt(100, 300) / 100.f;

	vel = (fTransform->getPos() - pos).normalize() * velMagnitude;
	
	int width = 25;
	int height = 25;

	auto misil = mngr->addEntity(ecs::grp::MISSILES);

	mngr->addComponent<Transform>(misil,pos,vel,width,height,0);
	mngr->addComponent<Image>(misil,"missile");
	mngr->addComponent<Follow>(misil,&fTransform->getPos());
	mngr->addComponent<LookAt>(misil, &fTransform->getPos());


}
