#include "ConstRotation.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"

ConstRotation::ConstRotation()
{
}

ConstRotation::ConstRotation(float angle) 
	: angle(angle)
{
}

ConstRotation::~ConstRotation()
{
}

void ConstRotation::initComponent()
{
	myTransform =  mngr_->getComponent<Transform>(ent_);
}

void ConstRotation::update()
{
	myTransform->setRot(myTransform->getRot() + angle);
}
