#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../components/MiracleFruit.h"
#include "../ecs/Manager.h"

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

		auto miracle = mngr_->getComponent<MiracleFruit>(msg.fruit_eaten_data.e);

		//si es una fruta milagrosa, avisa de que ha empezado la inmunidad(si no esta en inmunidad)
		if (!isImmune && miracle->miracleON) {

			isImmune = true;
			timeStart = sdlutils().virtualTimer().currTime();

			Message m;
			
			m.id = _m_IMMUNITY_START;

			mngr_->send(m,true);

		}
	}

}

void ImmunitySystem::updateImmnunity()
{
	if (!isImmune) return;//si no es inmmune no hacemos nada

	if (timeStart + immunityTime < sdlutils().virtualTimer().currTime()) {

		//si han pasado los 10 seg, se envia el mensaje
		Message m;

		m.id = _m_IMMUNITY_END;

		mngr_->send(m, true);
		//desactivar la inmmunidad
		isImmune = false;
	}


}
