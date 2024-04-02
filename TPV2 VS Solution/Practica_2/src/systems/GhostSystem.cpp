#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"


GhostSystem::GhostSystem()
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
}

void GhostSystem::update()
{
	//generar fantasmas
	generateGhosts();
	//mover fantasmas
	moveGhosts();

}

void GhostSystem::recieve(const Message& msg)
{
	if (msg.id == _m_PACMAN_GHOST_COLLISION) {

	}
	else if (msg.id == _m_IMMUNITY_START) {
		pacManImmune = true;
	}
	else if (msg.id == _m_IMMUNITY_END) {
		pacManImmune = false;
	}
	else if (msg.id == _m_ROUND_OVER) {
		destroyGhosts();
	}

}

void GhostSystem::generateGhosts()
{
	if (pacManImmune || mngr_->getEntities(ecs::grp::GHOSTS).size() >= 10) return;


	if (lastSpawn + ghostSpawnRate < sdlutils().virtualTimer().currTime()) {

		lastSpawn = sdlutils().virtualTimer().currTime();
		
		//creacion del nuevo fantasma
		auto newGhost = mngr_->addEntity(ecs::grp::GHOSTS);

		int width = 40;
		int height = 40;

		int fils = 8;
		int cols = 8;

		auto tf = mngr_->addComponent<Transform>(newGhost);
		auto img = mngr_->addComponent<ImageWithFrames>(newGhost,"spriteSheet",fils,cols);

		tf->setWidth(width);
		tf->setHeight(height);

		int rand = sdlutils().rand().nextInt(0, 4);

		//colocar el fantasama en una esquina aleatoria
		switch (rand)
		{
		case 0:
			img->firstIndex = 32;
			img->lastIndex = 39;
			img->currentFrame = 32;

			tf->getPos().set(0, 0);

			break;
		case 1:
			img->firstIndex = 40;
			img->lastIndex = 47;
			img->currentFrame = 40;

			tf->getPos().set(0, sdlutils().height()-height);

			break;
		case 2:
			img->firstIndex = 48;
			img->lastIndex = 55;
			img->currentFrame = 48;

			tf->getPos().set(sdlutils().width() -width, 0);

			break;
		case 3:
			img->firstIndex = 56;
			img->lastIndex = 63;
			img->currentFrame = 56;

			tf->getPos().set(sdlutils().width() - width, sdlutils().height() - height);

			break;

		default:
			break;
		}


	}
}

void GhostSystem::moveGhosts()
{
}

void GhostSystem::destroyGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		mngr_->setAlive(e, false);
	}
}
