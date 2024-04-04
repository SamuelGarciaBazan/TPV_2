#include "GameOverState.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"

//#include "../ecs/messages.h"

void GameOverState::update()
{
	messageTexture->render(messageRect);

	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::NEWGAME);

		Message m;

		m.id = _m_NEW_GAME;

		Game::instance()->getMngr()->send(m, true);
	}
}

void GameOverState::enter()
{
	if (true) {
		messageTexture = &sdlutils().msgs().at("game_over_win");
	}
	else {
		messageTexture = &sdlutils().msgs().at("game_over_lose");
	}


	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		(sdlutils().height() - messageTexture->height()) / 2,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

void GameOverState::leave()
{
}
