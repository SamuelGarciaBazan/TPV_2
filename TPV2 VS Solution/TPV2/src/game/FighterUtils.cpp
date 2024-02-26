#include "FighterUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"



void FighterUtils::create_fighter()
{
	auto mngr = Game::instance()->getMngr();

	//añadir la entidad al manager (FALTA GRUPO?/ HANDLER?)
	auto fighter =  mngr->addEntity();

	mngr->addComponent<Transform>(fighter);

	//transform

	//deAcceleration

	//image

	//health

	//fighterCrl

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
