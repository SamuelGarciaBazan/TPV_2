#pragma once
#include "GameState.h"
class RunningState :
    public GameState
{

public:

	RunningState();
	~RunningState();


	void update() override;
	void enter() override;
	void leave() override;
};

