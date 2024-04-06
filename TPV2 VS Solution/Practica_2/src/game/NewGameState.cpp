#include "NewGameState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"


NewGameState::NewGameState() 
{
	//text message
	messageTexture = &sdlutils().msgs().at("newgame");

	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		400,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

NewGameState::~NewGameState()
{

}

void NewGameState::update()
{
	

	SDL_Rect destinyRect{ 0,0,sdlutils().width(),sdlutils().height() };

	sdlutils().images().at("startBackground").render(destinyRect);

	//render message
	messageTexture->render(messageRect);

	if (ih().keyDownEvent()) {

		//cambiar al estado newRound
		Game::instance()->setState(Game::NEWROUND);
	}
	
}

void NewGameState::enter()
{

}

void NewGameState::leave()
{
}
