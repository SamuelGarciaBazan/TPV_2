#include "ScoreSystem.h"


ScoreSystem::ScoreSystem()
{
	font = &sdlutils().fonts().at("ARIAL24");

	destinationRect = SDL_Rect{ 680,20,100,40 };

	textColor = SDL_Color{255,255,255,1};
}

ScoreSystem::~ScoreSystem()
{
}

void ScoreSystem::initSystem()
{
}

void ScoreSystem::update()
{
	renderText();
}

void ScoreSystem::recieve(const Message& msg)
{
	if (msg.id == _m_PACMAN_SCORE_FOOD) {
		currentScore += foodScore;
	}
	else if (msg.id == _m_PACMAN_SCORE_GHOST) {
		currentScore += ghostScore;
	}
	else if (msg.id == _m_NEW_GAME) {
		currentScore = 0;
	}
}

void ScoreSystem::renderText()
{
	SDL_Surface* sur = font->renderText(std::string("Score: ")+ std::to_string(currentScore), textColor);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlutils().renderer(), sur);

	SDL_Rect sourceRect{0,0,sur->w,sur->h};

	SDL_RenderCopy(sdlutils().renderer(), texture, &sourceRect, &destinationRect);

}
