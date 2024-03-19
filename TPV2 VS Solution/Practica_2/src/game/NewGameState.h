#pragma once

#include "GameState.h"

class FighterFacade;

class NewGameState :
    public GameState
{
public:
	NewGameState(FighterFacade* fighter);
	~NewGameState();

	void update() override;
	void enter() override;
	void leave() override;

private:
	Texture* messageTexture;

	SDL_Rect messageRect;

	FighterFacade* fighter;

};

