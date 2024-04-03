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

		if (pacManImmune) {
			mngr_->setAlive(msg.ghost_collision_data.e, false);
		}
		else {

		}
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


		//velocidad inicial del fantasma

		auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;

		tf->vel_ = (posPM - tf->pos_).normalize() * 1.1f;


	}
}

void GhostSystem::moveGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		
		auto tf = mngr_->getComponent<Transform>(e);

		int rand = sdlutils().rand().nextInt(1, 1000);

		//randon chance para actualizar el vecto de velocidad
		if (rand < followChance) {

			auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;

			tf->vel_ = (posPM - tf->pos_).normalize() * 1.1f;
		}
			
		tf->pos_ = tf->pos_ + tf->vel_;


		//los fantasmas rebotan con los bordes
		if ((tf->pos_.getX() <= 0 && tf->vel_.getX() < -0.01) ||
			(tf->pos_.getX() >= (sdlutils().width() - tf->width_) && tf->vel_.getX() > 0.01)) {
			tf->vel_.set(-tf->vel_.getX(), tf->vel_.getY());
		}
		else if ((tf->pos_.getY() <= 0 && tf->vel_.getY() < -0.01) ||
			(tf->pos_.getY() >= (sdlutils().height() - tf->height_) && tf->vel_.getY() > 0.01)) {
			tf->vel_.set(tf->vel_.getX(), -tf->vel_.getY());
		}

	}

}

void GhostSystem::destroyGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		mngr_->setAlive(e, false);
	}
}
