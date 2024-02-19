#pragma once
#include "GameState.h"

class NewRoundState :
    public GameState
{
	void update() override;
	void enter() override;
	void leave() override;
};

