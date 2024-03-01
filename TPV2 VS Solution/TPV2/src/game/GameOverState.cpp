#include "GameOverState.h"

#include "Game.h"
#include "../ecs/Manager.h"



void GameOverState::update()
{
	messageTexture->render(messageRect);
}

void GameOverState::enter()
{
	if (Game::instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
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
