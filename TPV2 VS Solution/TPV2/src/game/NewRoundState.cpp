#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

NewRoundState::NewRoundState()
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

		//remove_all_asteroids (fachada)
		//...

		//create asteroids(10) (fachada)
		//...

		Game::instance()->setState(Game::RUNNING);
		

	}
}

void NewRoundState::enter()
{

}

void NewRoundState::leave()
{
}
