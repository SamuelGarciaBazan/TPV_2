#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/MiracleFruit.h"
#include "../game/Game.h"

FoodSystem::FoodSystem()
{
	fils = sdlutils().gameConstants().at("foodFils");
	cols = sdlutils().gameConstants().at("foodCols");

	spriteDefault = sdlutils().gameConstants().at("foodSpriteDefault");
	spriteMiracle = sdlutils().gameConstants().at("foodSpriteMiracle");
	
	
	miracleChance = sdlutils().gameConstants().at("foodChanceMiracle");
	 


}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
}

void FoodSystem::update()
{
	updateMiracleFruits();
}

void FoodSystem::recieve(const Message& msg)
{
	if (msg.id == _m_NEW_GAME) {
		destroyFruits();
		generateFruits();
	}
	else if (msg.id == m_PACMAN_FOOD_COLLISION) {
		//quitar fruta

		mngr_->setAlive(msg.fruit_eaten_data.e, false);

		//ºstd::cout << mngr_->getEntities(ecs::grp::FRUITS).size() << std::endl;

		sdlutils().soundEffects().at("eat").play();

		if (mngr_->getEntities(ecs::grp::FRUITS).size() == 1) {

			Message mRoundOver;

			mRoundOver.id = _m_ROUND_OVER;

			mngr_->send(mRoundOver,true);


			Message mGameOver;

			mGameOver.id = _m_GAME_OVER;
			
			mngr_->send(mGameOver, true);

			Game::instance()->setState(Game::GAMEOVER);

			sdlutils().soundEffects().at("won").play();


		}
	}
	else if (msg.id == _m_ROUND_START) {

		resetTimers();
	}
}

void FoodSystem::generateFruits()
{
	float offsetX;
	float offsetY;

	offsetX = sdlutils().width() / cols;
	offsetY = sdlutils().height() / fils;

	int fWidth = 25;
	int fHeight = 25;

	float firstCellX = (offsetX-fWidth)/2;
	float firstCellY = (offsetY-fHeight)/2;

	int n = fils * cols;


	for (int i = 0; i < n; i++) {

		auto newFruit = mngr_->addEntity(ecs::grp::FRUITS);

		auto tf = mngr_->addComponent<Transform>(newFruit);

		auto img = mngr_->addComponent<Image>(newFruit,"spriteSheet",8,8);

 		int random = sdlutils().rand().nextInt(0,1000);

		if (random < miracleChance) {

			mngr_->addComponent<MiracleFruit>(newFruit);
		
		}


		img->currentFrame = 12;

		tf->pos_.set(	firstCellX + (offsetX * (i % cols)),
						firstCellY + (offsetY * (i / cols)));
		tf->width_ = fWidth;
		tf->height_ = fHeight;

	}
}

void FoodSystem::resetTimers()
{
	for (auto& e : mngr_->getEntities(ecs::grp::FRUITS)) {

		auto miracleCmp = mngr_->getComponent<MiracleFruit>(e);
		auto img = mngr_->getComponent<Image>(e);
		
		if (miracleCmp != nullptr) {

			miracleCmp->resetTimer();
			img->currentFrame = spriteDefault;

		}


	}
}

void FoodSystem::updateMiracleFruits()
{
	for (auto& e : mngr_->getEntities(ecs::grp::FRUITS)) {

		auto miracleCmp = mngr_->getComponent<MiracleFruit>(e);
		auto img = mngr_->getComponent<Image>(e);

		if (miracleCmp != nullptr) {


			if (miracleCmp->miracleON) {
				//si ha pasado el tiempo
				if (miracleCmp->startTime + miracleCmp->miracleDuration < sdlutils().virtualTimer().currTime()) {
					miracleCmp->resetTimer();
					img->currentFrame = spriteDefault;
				}
			}
			else {

				//si ha pasado el tiempo
				if (miracleCmp->startTime + miracleCmp->miracleCooldown < sdlutils().virtualTimer().currTime()) {
					miracleCmp->startMiracle();
					img->currentFrame = spriteMiracle;

				}

			}

		}


	}

}

void FoodSystem::destroyFruits()
{

	for (auto& e : mngr_->getEntities(ecs::grp::FRUITS)) {
		mngr_->setAlive(e, false);
	}
}
