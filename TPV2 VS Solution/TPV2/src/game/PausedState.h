#pragma once
#include "GameState.h"

class Texture;

class PausedState :
    public GameState
{
public:

	PausedState();
	~PausedState();

	void update() override;
	void enter() override;
	void leave() override;

private:
	Texture* messageTexture;


	SDL_Rect messageRect;
};

