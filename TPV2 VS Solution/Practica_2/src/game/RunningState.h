#pragma once
#include "GameState.h"


class FighterFacade;
class AsteroidsFacade;
class MissilesFacade;

class Transform;

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

	void spawnAsteroids();
	void spawnMissiles();

	void collisions();

	void collisionsAsteroids();

	void collisionsBlackHolesFigher();

	void collisionsMissiles();



	bool collidesWithRotation(Transform* t1, Transform* t2);

	void fighterDeath();

	//facades
	FighterFacade* fighter;
	AsteroidsFacade* asteorids;
	MissilesFacade* missiles;


	//timers && spawn rates
	uint32_t lastGeneration = 0;
	uint16_t asteroidSpawnRate = 5000;


	uint32_t lastMissile = 0;
	uint16_t missileSpawnRate = 15000;
};

