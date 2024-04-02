#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"


ImmunitySystem::ImmunitySystem()
{
}

ImmunitySystem::~ImmunitySystem()
{
}

void ImmunitySystem::initSystem()
{
}

void ImmunitySystem::update()
{
	updateImmnunity();
}

void ImmunitySystem::recieve(const Message& msg)
{
	if (msg.id == m_PACMAN_FOOD_COLLISION) {
		//si es una fruta milagrosa, avisa de que ha empezado la inmunidad(si no esta en inmunidad)
		if (!isImmune && false) {
			//falta comprobar que la fruta es milagrosa


			isImmune = true;
			timeStart = sdlutils().virtualTimer().currTime();
		}
	}

}

void ImmunitySystem::updateImmnunity()
{
	if (!isImmune) return;//si no es inmmune no hacemos nada

	if (timeStart + immunityTime < sdlutils().virtualTimer().currTime()) {

		//si han pasado los 10 seg, se envia el mensaje

		//desactivar la inmmunidad
		isImmune = false;
	}


}
