#include "FighterUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/Health.h"
#include "../components/Gun.h"

void FighterUtils::create_fighter()
{
	auto mngr = Game::instance()->getMngr();

	//añadir la entidad al manager (FALTA GRUPO?/ HANDLER?)
	auto fighter =  mngr->addEntity();

	mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	//transform
	transform = mngr->addComponent<Transform>(fighter);

	//deAcceleration
	mngr->addComponent<DeAcceleration>(fighter);

	//image
	image = mngr->addComponent<Image>(fighter,"fighter");

	//health
	health =  mngr->addComponent<Health>(fighter, "heart",0.35);

	//fighterCrl
 	mngr->addComponent<FighterCtrl>(fighter);
	//gun 
	gun = mngr->addComponent<Gun>(fighter);
	//showAtOpposie site
	mngr->addComponent<ShowAtOpposieSide>(fighter);


	
}

void FighterUtils::reset_fighter()
{
	transform->getPos().set((sdlutils().width() - image->getTexture().width()) / 2,
		(sdlutils().height() - image->getTexture().height()) / 2);
	transform->setRot(0);
	transform->getVel().set(0, 0);

	//reset de las balas
	auto it = gun->begin();
	while (it != gun->end()) { (*it).used = false; ++it; }


}

void FighterUtils::reset_lives()
{
	health->resetLifes();
}

int FighterUtils::update_lives(int n)
{
	return 0;
}
