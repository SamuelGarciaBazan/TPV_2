#include "FoodSystem.h"

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
}

void FoodSystem::updateMiracleFruits()
{
}
