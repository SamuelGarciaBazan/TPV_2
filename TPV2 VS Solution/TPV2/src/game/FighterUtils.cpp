#include "FighterUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"




void FighterUtils::create_fighter()
{
	auto mngr = Game::instance()->getMngr();

	//añadir la entidad al manager (FALTA GRUPO?/ HANDLER?)
	auto fighter =  mngr->addEntity();


	//transform
	mngr->addComponent<Transform>(fighter);

	//deAcceleration
	
	//image
	mngr->addComponent<Image>(fighter,"fighter");

	//health

	//fighterCrl
	mngr->addComponent<FighterCtrl>(fighter);
	//gun 

	//showAtOpposie site


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
