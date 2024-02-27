#include "DeAcceleration.h"
#include "Transform.h"
#include "../ecs/Manager.h"


DeAcceleration::DeAcceleration()
{
}

DeAcceleration::~DeAcceleration()
{
}

void DeAcceleration::update()
{
	myTransform->getVel().set(myTransform->getVel()*deAcelerationRate);
	if (myTransform->getVel().magnitude() < minVel) {
		myTransform->getVel().set(0, 0);
	}

}

void DeAcceleration::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	assert(myTransform != nullptr);
}
