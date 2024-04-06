#include "PausedState.h"
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"

#include "Game.h"

PausedState::PausedState()
{
	messageTexture = &sdlutils().msgs().at("paused");

	//rect, center screen
	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,//x
		(sdlutils().height() - messageTexture->height()) / 2,//y
		messageTexture->width(), messageTexture->height()); // w / h
}

PausedState::~PausedState()
{
}

void PausedState::update()
{
	SDL_Rect destinyRect{ 0,0,sdlutils().width(),sdlutils().height() };

	sdlutils().images().at("playBackground").render(destinyRect);

	messageTexture->render(messageRect);

	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::RUNNING);
	}
}

void PausedState::enter()
{
	sdlutils().virtualTimer().pause();
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();

}
