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

	mngr_->setHandler(ecs::hdlr::PACMAN, pacMan);

	float healthImageScale = 0.35;

	int fils = 8;
	int cols = 8;

	//añadir componentes
	auto trasnformCmp = mngr_->addComponent<Transform>(pacMan);
	auto imgF_Cmp = mngr_->addComponent<ImageWithFrames>(pacMan,"spriteSheet",fils,cols);
	auto healthCmp =  mngr_->addComponent<Health>(pacMan,"heart",healthImageScale);

	
	trasnformCmp->setHeight(pacmanHeight);
	trasnformCmp->setWidth(pacmanWidth);

	resetPos();
	resetLifes();

	imgF_Cmp->firstIndex = 0;
	imgF_Cmp->lastIndex = 3;

}

void PacManSystem::update()
{
	//mover el pacman
	movePacMan();
}

void PacManSystem::recieve(const Message& msg)
{
	if (msg.id == _m_ROUND_START) {
		//nueva ronda, resetear posicion
		resetPos();
	}
	else if (msg.id == _m_NEW_GAME) {
		//nueva partida resetear vidas
		resetLifes();
	}	
}

void PacManSystem::movePacMan()
{
	auto tf = mngr_->getComponent<Transform>(pacMan);


	if (ih().isKeyDown(SDL_SCANCODE_UP)) {
		//setear la velocidad y rotar
		tf->getVel().set(0, -pacManVel);
		tf->getVel() = tf->getVel().rotate(tf->rot_);
	}
	if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
		tf->getVel().set(0, 0);
	}
	if (ih().isKeyDown(SDL_SCANCODE_RIGHT) && !rightPressed) {
		tf->rot_ += 90;
		tf->getVel() = tf->getVel().rotate(90);
		rightPressed = true;
	}
	if (ih().isKeyDown(SDL_SCANCODE_LEFT) && !leftPressed) {
		tf->rot_ -= 90;
		tf->getVel() = tf->getVel().rotate(-90);
		leftPressed = true;
	}

	if (ih().isKeyUp(SDL_SCANCODE_RIGHT)) {
		rightPressed = false;
	}
	if (ih().isKeyUp(SDL_SCANCODE_LEFT)) {
		leftPressed = false;
	}

	if (tf->vel_.getX() != 0 && 
		tf->vel_.getY() != 0) {

		std::cout << tf->vel_ << std::endl;
	}

	if ( (tf->pos_.getX() <= 0 && tf->vel_.getX() < -0.01) ||
		 (tf->pos_.getY() <= 0 && tf->vel_.getY() < -0.01) || 
	     (tf->pos_.getX() >= (sdlutils().width()  - tf->width_) && tf->vel_.getX() > 0.01) ||
		 (tf->pos_.getY() >= (sdlutils().height() - tf->height_) && tf->vel_.getY() >  0.01)) {

		tf->vel_.set(0, 0);
	}

	tf->pos_ = tf->pos_ + tf->vel_;
}

void PacManSystem::resetPos()
{
	auto tf = mngr_->getComponent<Transform>(pacMan);

	tf->getPos().set((sdlutils().width() - pacmanWidth) / 2,
		(sdlutils().height() - pacmanHeight) / 2);
}

void PacManSystem::resetLifes()
{
	auto healthCmp = mngr_->getComponent<Health>(pacMan);

	healthCmp->setLifes(3);

}



