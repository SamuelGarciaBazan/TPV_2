#include "GhostSystem.h"

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

	}
	else if (msg.id == _m_IMMUNITY_END) {

	}

}

void GhostSystem::generateGhosts()
{
}

void GhostSystem::moveGhosts()
{
}
