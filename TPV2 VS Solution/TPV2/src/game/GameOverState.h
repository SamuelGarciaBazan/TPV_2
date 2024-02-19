#pragma once
#include "GameState.h"
class GameOverState :
    public GameState
{
	void update() override;
	void enter() override;
	void leave() override;

};

