#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"
#include "../components/Weak.h"
#include "../components/Ghost.h"
#include "../game/Game.h"

GhostSystem::GhostSystem()
{
	followFactor = sdlutils().gameConstants().at("ghostsVelocity");

	ghostSpawnRate = sdlutils().gameConstants().at("ghostSpawnRate");

	followChance = sdlutils().gameConstants().at("ghostFollowChance");
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

			Message mScore;
			mScore.id = _m_PACMAN_SCORE_GHOST;

			mngr_->send(mScore, true);
		}
		else {
			auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);

			auto health = mngr_->getComponent<Health>(pacMan);

			health->currentLifes--;

			Message msgRoundOver;

			msgRoundOver.id = _m_ROUND_OVER;

			mngr_->send(msgRoundOver, true);

			sdlutils().soundEffects().at("death").play();

			if (health->currentLifes <= 0) {

				Message msgNewGame;

				msgNewGame.id = _m_NEW_GAME;

				mngr_->send(msgNewGame, true);

				Game::instance()->setState(Game::GAMEOVER);
			}
			else {		
				Game::instance()->setState(Game::NEWROUND);		
			}
		}
	}
	else if (msg.id == _m_PACMAN_GHOST_WEAK_COLLISION) {


		if (pacManImmune) {
			mngr_->setAlive(msg.ghost_collision_data.e, false);

			Message mScore;
			mScore.id = _m_PACMAN_SCORE_GHOST;

			mngr_->send(mScore, true);
		}
		else {
			auto weakCmp = mngr_->getComponent<Weak>(msg.ghost_collision_data.e);

			weakCmp->nCol--;

			if (weakCmp->nCol <= 0) {

				Message msg_;
				msg_.id = _m_PACMAN_GHOST_COLLISION;

				msg_.ghost_collision_data.e = msg.ghost_collision_data.e;

				mngr_->send(msg_, true);

#ifdef _DEBUG
				std::cout << "Muere fantasma debil" << std::endl;
				std::cout << weakCmp->nCol << std::endl;
#endif // DEBUG
			}
			else {
				//devolver a su posicion 

				auto tf = mngr_->getComponent<Transform>(msg.ghost_collision_data.e);


				tf->pos_ = weakCmp->initialPos;


#ifdef _DEBUG
				std::cout << "Devuelve pos fantasma debil" << std::endl;
				std::cout << tf->pos_ << std::endl;
				std::cout << tf->vel_ << std::endl;
#endif // DEBUG

				if (weakCmp->nCol <= 1) {

					auto img = mngr_->getComponent<ImageWithFrames>(msg.ghost_collision_data.e);

					img->firstIndex = 32;
					img->lastIndex = 39;
					img->currentFrame = 32;
				}

			}
		}
		
	}

	else if (msg.id == _m_IMMUNITY_START) {
		pacManImmune = true;
		handleInmmunityStart();
	}
	else if (msg.id == _m_IMMUNITY_END) {
		pacManImmune = false;
		handleInmmunityEnd();
	}
	else if (msg.id == _m_ROUND_OVER) {
		destroyGhosts();
	}
	else if (msg.id == _m_ROUND_START) {

		//actualizar el contador de tiempo
		lastSpawn = sdlutils().virtualTimer().currTime();
	}
	else if (msg.id == _m_ENTER_SAFE_MODE) {

		for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
			auto ghsCmp = mngr_->getComponent<Ghost>(e);
			ghsCmp->move = false;
		}	
	}
	else if (msg.id == _m_EXIT_SAFE_MODE) {
		for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
			auto ghsCmp = mngr_->getComponent<Ghost>(e);
			ghsCmp->move = true;
		}
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
		auto ghCmpt = mngr_->addComponent<Ghost>(newGhost);

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
			img->firstIndex = 32;
			img->lastIndex = 39;
			//img->firstIndex = 40;
			//img->lastIndex = 47;
			img->currentFrame = 32;


			tf->getPos().set(0, sdlutils().height()-height);

			break;
		case 2:
			img->firstIndex = 32;
			img->lastIndex = 39;
			//img->firstIndex = 48;
			//img->lastIndex = 55;
			//img->currentFrame = 48;
			img->currentFrame = 32;



			tf->getPos().set(sdlutils().width() -width, 0);

			break;
		case 3:
			img->firstIndex = 32;
			img->lastIndex = 39;
			//img->firstIndex = 56;
			//img->lastIndex = 63;
			//img->currentFrame = 56;
			img->currentFrame = 32;



			tf->getPos().set(sdlutils().width() - width, sdlutils().height() - height);

			break;

		default:
			break;
		}


		//velocidad inicial del fantasma

		auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;

		tf->vel_ = (posPM - tf->pos_).normalize() * 1.1f;

		//decidir si el fantasma es un fantasma debil

		if (sdlutils().rand().nextInt(0, 1000) <= weakChance) {

			int nChoques = sdlutils().rand().nextInt(minWeakCollisions, maxWeakCollisions);


			mngr_->addComponent<Weak>(newGhost, nChoques,tf->getPos());

			//si es fantasma debil cambiamos el color
			img->firstIndex = 56;
			img->lastIndex = 63;
			img->currentFrame = 56;

#ifdef _DEBUG
			std::cout << "Creado fantasma debil" << std::endl;
#endif // DEBUG

		}


		


	}
}

void GhostSystem::moveGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		
		auto ghsCmp = mngr_->getComponent<Ghost>(e);

		if (!ghsCmp->move) continue;

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

void GhostSystem::handleInmmunityStart()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {

		auto weak = mngr_->getComponent<Weak>(e);

		if (weak != nullptr) {

			auto img = mngr_->getComponent<ImageWithFrames>(e);

			img->firstIndex = 32;
			img->lastIndex = 39;
			img->currentFrame = 32;
		}
	}


}

void GhostSystem::handleInmmunityEnd()
{

	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {

		auto weak = mngr_->getComponent<Weak>(e);

		if (weak != nullptr && weak->nCol >1) {

			auto img = mngr_->getComponent<ImageWithFrames>(e);

			img->firstIndex = 56;
			img->lastIndex = 63;
			img->currentFrame = 56;
		}
	}
}
