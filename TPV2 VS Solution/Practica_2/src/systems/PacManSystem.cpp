#include "PacManSystem.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


PacManSystem::PacManSystem()
{
}

PacManSystem::~PacManSystem()
{
}

void PacManSystem::initSystem()
{
	//creacion del pacMan
	pacMan = mngr_->addEntity();

	float healthImageScale = 0.35;

	int fils = 8;
	int cols = 8;

	int pacmanWidth = 40;
	int pacmanHeight = 40;

	//añadir componentes
	auto trasnformCmp = mngr_->addComponent<Transform>(pacMan);
	auto imgF_Cmp = mngr_->addComponent<ImageWithFrames>(pacMan,"spriteSheet",fils,cols);
	auto healthCmp =  mngr_->addComponent<Health>(pacMan,"heart",healthImageScale);

	healthCmp->setLifes(3);
	
	trasnformCmp->setHeight(pacmanHeight);
	trasnformCmp->setWidth(pacmanWidth);

	trasnformCmp->getPos().set(	(sdlutils().width() -pacmanWidth)/2,
								(sdlutils().height()-pacmanHeight)/2);

	imgF_Cmp->firstIndex = 0;
	imgF_Cmp->lastIndex = 3;

	lastInput = sdlutils().virtualTimer().currTime();


}

void PacManSystem::update()
{
	//mover el pacman
	//mngr_->update();

	auto tf = mngr_->getComponent<Transform>(pacMan);


	if (lastInput + inputDelay <= sdlutils().virtualTimer().currTime()) {

		if (ih().isKeyDown(SDL_SCANCODE_UP)) {
			 tf->getVel().set(0, -pacManVel);
			 tf->getVel() = tf->getVel().rotate(tf->rot_);
			lastInput = sdlutils().virtualTimer().currTime();
		}
		if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
			tf->getVel().set(0, 0);
			lastInput = sdlutils().virtualTimer().currTime();

		}
		if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
			tf->rot_ += 90;
			tf->getVel().set(0, -pacManVel);

			tf->getVel() = tf->getVel().rotate(tf->rot_);
			lastInput = sdlutils().virtualTimer().currTime();
		}
		if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {

			tf->rot_ -= 90;
			tf->getVel().set(0, -pacManVel);

			tf->getVel()= tf->getVel().rotate(tf->rot_);
			lastInput = sdlutils().virtualTimer().currTime();

		}
	}

	
	tf->pos_ = tf->pos_ + tf->vel_;

	std::cout << tf->vel_ << std::endl;
	
	animatePacMan();
}

void PacManSystem::recieve(const Message& msg)
{
	
	if (msg.id == _m_ROUND_START) {
		//nueva ronda, resetear posicion

	}
	else if (msg.id == _m_NEW_GAME) {
		//nueva partida resetear vidas

	}

		
}

void PacManSystem::animatePacMan()
{
	//update del imageWithFrames, Animacion del pacman
	auto imgF_Cmp = mngr_->getComponent<ImageWithFrames>(pacMan);


	if ((imgF_Cmp->lastFrame + imgF_Cmp->frameTime) < sdlutils().virtualTimer().currTime()) {

		imgF_Cmp->lastFrame = sdlutils().virtualTimer().currTime();
		imgF_Cmp->currentFrame++;
		if (imgF_Cmp->currentFrame > imgF_Cmp->lastIndex) {
			imgF_Cmp->currentFrame = imgF_Cmp->firstIndex;
		}
	}

	imgF_Cmp->render();//cambiar al render system??
}
