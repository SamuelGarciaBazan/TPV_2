#include "TowardDestination.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

TowardDestination::TowardDestination()
	:destPos(newDest())
{
	
}

TowardDestination::~TowardDestination()
{
}

void TowardDestination::update()
{
	if ((destPos - myTransform->getPos()).magnitude() < 10.0) {

		destPos = newDest();
		myTransform->getVel().set(newVelVector());
	}
}

void TowardDestination::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	myTransform->getVel().set(newVelVector());

}

Vector2D TowardDestination::newDest()
{
	return Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()),
		sdlutils().rand().nextInt(0, sdlutils().height()));
}

Vector2D TowardDestination::newVelVector()
{
	return Vector2D(myTransform->getVel().rotate(
		myTransform->getVel().angle(destPos - myTransform->getPos())));
}
