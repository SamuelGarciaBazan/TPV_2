#include "Follow.h"
#include "../ecs/Manager.h"
#include "Transform.h"

#include "../utils/Vector2D.h"


Follow::Follow(Vector2D* fighterPos) 
	:fighterPos(fighterPos)
{
}

Follow::~Follow()
{
}

void Follow::update()
{
	myTransform->getVel().set(myTransform->getVel().rotate(myTransform->getVel().angle(*fighterPos - myTransform->getPos()) > 0 ?
		1.0f : -1.0f));
}

void Follow::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
}
