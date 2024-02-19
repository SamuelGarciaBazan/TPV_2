#pragma once
#include "GameState.h"
class RunningState :
    public GameState
{
	void update() override;
	void enter() override;
	void leave() override;
};

