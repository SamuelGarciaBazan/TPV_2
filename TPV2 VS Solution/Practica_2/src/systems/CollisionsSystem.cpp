#include "CollisionsSystem.h"

CollisionsSystem::CollisionsSystem()
{
}

CollisionsSystem::~CollisionsSystem()
{
}

void CollisionsSystem::initSystem()
{
}

void CollisionsSystem::update()
{
	checkCollisions();
}

void CollisionsSystem::recieve(const Message& msg)
{
}

void CollisionsSystem::checkCollisions()
{
	//comprobar colisiones y enviar los mensajes correspondientes
}
