#include "PacManSystem.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"

#include "../sdlutils/SDLUtils.h"


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



}

void PacManSystem::update()
{
	//mover el pacman
	//mngr_->update();

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
