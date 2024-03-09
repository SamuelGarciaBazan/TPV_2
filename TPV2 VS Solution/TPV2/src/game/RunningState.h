#pragma once
#include "GameState.h"


class FighterFacade;
class AsteroidsFacade;
class MissilesFacade;

class RunningState :
    public GameState
{

public:

	RunningState(FighterFacade* fighter, AsteroidsFacade* asteorids,
		MissilesFacade* missiles);
	~RunningState();


	void update() override;
	void enter() override;
	void leave() override;

private:

	FighterFacade* fighter;
	AsteroidsFacade* asteorids;
	MissilesFacade* missiles;

	uint32_t lastGeneration = 0;
	uint16_t asteroidSpawnRate = 5000;


	uint32_t lastMissile = 0;
	uint16_t missileSpawnRate = 15000;
};

