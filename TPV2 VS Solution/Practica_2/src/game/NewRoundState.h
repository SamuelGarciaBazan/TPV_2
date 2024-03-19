#pragma once
#include "GameState.h"

class FighterFacade;
class AsteroidsFacade;
class BlackHolesFacade;
class MissilesFacade;

class NewRoundState :
    public GameState
{
public:
	NewRoundState(FighterFacade* fighter, AsteroidsFacade* asteorids,
				BlackHolesFacade* blackHoles, MissilesFacade*missiles) ;
	~NewRoundState();

	void update() override;
	void enter() override;
	void leave() override;

private:

	Texture* messageTexture;

	SDL_Rect messageRect;

	FighterFacade* fighter;
	AsteroidsFacade* asteorids;
	BlackHolesFacade* blackHoles;
	MissilesFacade* missiles;
};

