#include "BlackHolesUtils.h"

#include "../utils/Vector2D.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../ecs/ecs.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ConstRotation.h"

BlackHolesUtils::BlackHolesUtils()
{
}

BlackHolesUtils::~BlackHolesUtils()
{
}

void BlackHolesUtils::create_black_holes(int n)
{
	float angle = 360.f / n;
	Vector2D pos;


	for (int i = 0; i < n; i++) {
		int radius = sdlutils().rand().nextInt(100,300);
		pos = Vector2D(sdlutils().width()/2, sdlutils().height()/2) + Vector2D(0, -radius).rotate(angle * i);

		create_black_hole(pos);
	}
}

void BlackHolesUtils::remove_all_black_holes()
{
	auto mngr = Game::instance()->getMngr();
	for (auto& e : mngr->getEntities(ecs::grp::BLACKHOLES)) {
		mngr->setAlive(e, false);
	}

	mngr->refresh();
}

void BlackHolesUtils::create_black_hole(Vector2D pos)
{
	auto mngr = Game::instance()->getMngr();

	auto bh =  mngr->addEntity(ecs::grp::BLACKHOLES);

	int width = 30;
	int height = 30;

	float rotation = sdlutils().rand().nextInt(200, 500) / 100.f;

	mngr->addComponent<Transform>(bh,pos,Vector2D(0,0), width, height, 0);
	mngr->addComponent<Image>(bh,"blackHole");
	mngr->addComponent<ConstRotation>(bh,rotation);
	
	
}
