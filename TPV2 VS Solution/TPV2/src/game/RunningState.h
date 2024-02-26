#pragma once
#include "GameState.h"


class FighterFacade;
class AsteroidsFacade;

class RunningState :
    public GameState
{

public:

	RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids);
	~RunningState();


	void update() override;
	void enter() override;
	void leave() override;

private:

	FighterFacade* fighter;
	AsteroidsFacade* asteorids;
};

