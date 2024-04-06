#include "NewRoundState.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"

NewRoundState::NewRoundState()
{
	messageTexture = &sdlutils().msgs().at("newround");

	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		400,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

NewRoundState::~NewRoundState()
{
}

void NewRoundState::update()
{

	SDL_Rect destinyRect{ 0,0,sdlutils().width(),sdlutils().height() };
	//renderBackground
	sdlutils().images().at("startBackground").render(destinyRect);

	//renderMessage
	messageTexture->render(messageRect);

	if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {

		Game::instance()->setState(Game::RUNNING);


		//lanzar mensaje
		Message msg;

		msg.id = _m_ROUND_START;

		Game::instance()->getMngr()->send(msg, true);
	}
}

void NewRoundState::enter()
{

}

void NewRoundState::leave()
{
}
