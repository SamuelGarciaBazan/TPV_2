#include "LookAt.h"

#include "../ecs/Manager.h"
#include "Transform.h"

LookAt::LookAt(Vector2D* target)
	:target(target)
{
}

LookAt::~LookAt()
{
}

void LookAt::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
}

void LookAt::update()
{
	myTransform->setRot(Vector2D(0, -1).angle(myTransform->getVel()));
}
