#pragma once
#include "GameState.h"


class Texture;

class GameOverState :
    public GameState
{
public:
	void update() override;
	void enter() override;
	void leave() override;

private:
	Texture* messageTexture;


	SDL_Rect messageRect;
};
