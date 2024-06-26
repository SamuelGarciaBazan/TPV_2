#pragma once
#include "GameState.h"

class Transform;

class PacManSystem;
class GhostSystem;
class FoodSystem;
class ImmunitySystem;
class CollisionsSystem;
class RenderSystem;
class ScoreSystem;
class SafeSystem;


class RunningState :
    public GameState
{

public:

	RunningState(PacManSystem*,GhostSystem*,FoodSystem*,
				ImmunitySystem*,CollisionsSystem*,RenderSystem*,ScoreSystem*, SafeSystem*);
	~RunningState();

	void update() override;
	void enter() override;
	void leave() override;

private:


	PacManSystem* pacManSystem;
	GhostSystem* ghostSystem;
	FoodSystem* foodSystem;
	ImmunitySystem* immunitySystem;
	CollisionsSystem* collisionsSystem;
	RenderSystem* renderSystem;
	ScoreSystem* scoreSystem;
	SafeSystem* safeSystem;
};

