#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

#include "FighterFacade.h"
#include "AsteroidsFacade.h"
#include "BlackHolesFacade.h"
#include "MissilesFacade.h"

NewRoundState::NewRoundState(FighterFacade* fighter, AsteroidsFacade* asteorids, 
	BlackHolesFacade* blackHoles, MissilesFacade* missiles)
	:fighter(fighter), asteorids(asteorids),blackHoles(blackHoles),missiles(missiles)
{
	messageTexture = &sdlutils().msgs().at("newround");

	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		(sdlutils().height() - messageTexture->height()) / 2,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

NewRoundState::~NewRoundState()
{
}

void NewRoundState::update()
{
	messageTexture->render(messageRect);

	if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {

		//reset fighter(fachada)
		//...
		fighter->reset_fighter();

		//remove_all_asteroids (fachada)
		//...
		asteorids->remove_all_asteroids();

		//create asteroids(10) (fachada)
		//...
		asteorids->create_asteroids(sdlutils().gameConstants().at("nAsteroids"));

		blackHoles->remove_all_black_holes();


		blackHoles->create_black_holes(5);

		missiles->remove_all_missiles();

		//missiles->createMisile();

		Game::instance()->setState(Game::RUNNING);
		

	}
}

void NewRoundState::enter()
{

}

void NewRoundState::leave()
{
}
