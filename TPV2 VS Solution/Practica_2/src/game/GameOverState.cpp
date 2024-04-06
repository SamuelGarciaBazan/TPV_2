#include "GameOverState.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"

#include "../components/Health.h"


void GameOverState::update()
{
	SDL_Rect destinyRect{ 0,0,sdlutils().width(),sdlutils().height() };
	//render background
	sdlutils().images().at("playBackground").render(destinyRect);

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
	

	auto mngr = Game::instance()->getMngr();

	auto pacman = mngr->getHandler(ecs::hdlr::PACMAN);

	auto health = mngr->getComponent<Health>(pacman);

	if (  health->currentLifes >0 ) {
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
