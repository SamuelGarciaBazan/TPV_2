// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "GameOverState.h"
#include "NewGameState.h"
#include "NewRoundState.h"

#include "PausedState.h"
#include "RunningState.h"

using ecs::Manager;

Game::Game() :
		mngr_(new Manager()), //
		ihdlr(ih()), //
		current_state_(nullptr), //
		paused_state_(nullptr), //
		runing_state_(nullptr), //
		newgame_state_(nullptr), //
		newround_state_(nullptr), //
		gameover_state_(nullptr) {

}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("ASTEROIDS", 800, 600,
			"resources/config/pacman.resources.json","resources/config/pacman.config.json");

	//creacion de estados
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	runing_state_ = new RunningState();
	paused_state_ = new PausedState();
	gameover_state_ = new GameOverState();

	current_state_ = newgame_state_;
	newgame_state_->enter();

	//creacion de los sistemas



}

void Game::start() {

// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		//clear rendering
		sdlutils().clearRenderer();

		// refresh the input handler
		ihdlr.refresh();

		//exit game
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		
		//update state
		current_state_->update();

		//render
		sdlutils().presentRenderer();

		//envio de mensajes
		mngr_->flushMessagesWithSwap();

		//sleep the process
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
	
}

