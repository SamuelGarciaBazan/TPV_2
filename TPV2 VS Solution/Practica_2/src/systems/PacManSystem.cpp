#include "PacManSystem.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"



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

	float healthImageScale = 1.f;

	int fils = 3;
	int cols = 3;

	mngr_->addComponent<Transform>(pacMan);
	mngr_->addComponent<ImageWithFrames>(pacMan,"id",fils,cols);
	mngr_->addComponent<Health>(pacMan,"heart",healthImageScale);


}

void PacManSystem::update()
{
	//mover el pacman


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
