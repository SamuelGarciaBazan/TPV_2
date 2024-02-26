#pragma once
#include "GameState.h"

class FighterFacade;
class AsteroidsFacade;

class NewRoundState :
    public GameState
{
public:
	NewRoundState();
	~NewRoundState();

	void update() override;
	void enter() override;
	void leave() override;

private:

	Texture* messageTexture;

	SDL_Rect messageRect;

	FighterFacade* fighter;
	AsteroidsFacade* asteorids;
};

