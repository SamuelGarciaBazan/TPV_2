#pragma once
#include "GameState.h"

class Transform;

class RunningState :
    public GameState
{

public:

	RunningState();
	~RunningState();

	void update() override;
	void enter() override;
	void leave() override;

private:

	void collisions();

	bool collidesWithRotation(Transform* t1, Transform* t2);

};

