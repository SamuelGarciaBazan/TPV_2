#include "CollisionsSystem.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../components/Weak.h"
#include "../components/ImageWithFrames.h"

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

	auto pair1 = collisionsGhosts();

	if (pair1.first) {

		auto weakCmp = mngr_->getComponent<Weak>(pair1.second);

		if (weakCmp != nullptr) {

			Message msg;
			msg.id = _m_PACMAN_GHOST_WEAK_COLLISION;

			msg.ghost_collision_data.e = pair1.second;

			mngr_->send(msg, true);
		}

		else {

			Message msg;
			msg.id = _m_PACMAN_GHOST_COLLISION;

			msg.ghost_collision_data.e = pair1.second;

			mngr_->send(msg, true);
		}

	}
	auto pair2 = collisionsFood();
	if (pair2.first) {
		Message msg;
		msg.id = m_PACMAN_FOOD_COLLISION;
		
		msg.fruit_eaten_data.e = pair2.second;

		mngr_->send(msg, true);
	}
}

std::pair<bool, ecs::entity_t> CollisionsSystem::collisionsGhosts()
{
	auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto ghosts = mngr_->getEntities(ecs::grp::GHOSTS);

	int i = 0;

	while (i < ghosts.size() && !collidesWithRotation(mngr_->getComponent<Transform>(pacMan),
			mngr_->getComponent<Transform>(ghosts[i]))) i++;

	return { i < ghosts.size(),i < ghosts.size() ? ghosts[i] : nullptr};
}

std::pair<bool, ecs::entity_t> CollisionsSystem::collisionsFood()
{
	auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto food = mngr_->getEntities(ecs::grp::FRUITS);

	int i = 0;

	while (i < food.size() &&  !collidesWithRotation(mngr_->getComponent<Transform>(pacMan),
		mngr_->getComponent<Transform>(food[i]))) i++;

	return { i < food.size(),i < food.size() ? food[i] : nullptr };
}

bool CollisionsSystem::collidesWithRotation(Transform* t1, Transform* t2)
{
	return Collisions::collidesWithRotation(
		t1->getPos(), t1->getWidth(), t1->getHeight(), t1->getRot(),
		t2->getPos(), t2->getWidth(), t2->getHeight(), t2->getRot());	
}
