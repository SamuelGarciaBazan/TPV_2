#include "FighterUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/ShowAtOpposieSide.h"



void FighterUtils::create_fighter()
{
	auto mngr = Game::instance()->getMngr();

	//añadir la entidad al manager (FALTA GRUPO?/ HANDLER?)
	auto fighter =  mngr->addEntity();


	//transform
	Transform* transform = mngr->addComponent<Transform>(fighter);

	//deAcceleration
	mngr->addComponent<DeAcceleration>(fighter);

	//image
	Image* image = mngr->addComponent<Image>(fighter,"fighter");

	//health

	//fighterCrl
 	mngr->addComponent<FighterCtrl>(fighter);
	//gun 

	//showAtOpposie site
	mngr->addComponent<ShowAtOpposieSide>(fighter);


	transform->getPos().set((sdlutils().width() - image->getTexture().width() ) / 2,
							(sdlutils().height() - image->getTexture().height()) / 2);
}

void FighterUtils::reset_fighter()
{
}

void FighterUtils::reset_lives()
{
}

int FighterUtils::update_lives(int n)
{
	return 0;
}
