#pragma once

#include "GameState.h"

class NewGameState :
    public GameState
{
	void update() override;
	void enter() override;
	void leave() override;
};

