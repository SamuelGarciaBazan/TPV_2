#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"

FoodSystem::FoodSystem()
{
	

}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
}

void FoodSystem::update()
{
}

void FoodSystem::recieve(const Message& msg)
{
	if (msg.id == _m_NEW_GAME) {
		generateFruits();
	}
	else if (msg.id == m_PACMAN_FOOD_COLLISION) {
		//quitar fruta
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

		img->currentFrame = 12;

		tf->pos_.set(	firstCellX + (offsetX * (i % cols)),
						firstCellY + (offsetY * (i / cols)));
		tf->width_ = fWidth;
		tf->height_ = fHeight;

	}
}

void FoodSystem::updateMiracleFruits()
{




}
