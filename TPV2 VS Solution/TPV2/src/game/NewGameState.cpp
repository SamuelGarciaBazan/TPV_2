#include "NewGameState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

#include "FighterFacade.h"

NewGameState::NewGameState(FighterFacade* fighter) : fighter(fighter)
{
	//text message
	messageTexture = &sdlutils().msgs().at("newgame");

	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		(sdlutils().height() - messageTexture->height()) / 2,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

NewGameState::~NewGameState()
{

}

void NewGameState::update()
{
	//render message
	messageTexture->render(messageRect);

	
	if (ih().keyDownEvent()) {

		//resetear vidas del caza(con facade)
		//...
		fighter->reset_lives();
		
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
