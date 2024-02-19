#pragma once
#include "GameState.h"
class PausedState :
    public GameState
{
	void update() override;
	void enter() override;
	void leave() override;

};

