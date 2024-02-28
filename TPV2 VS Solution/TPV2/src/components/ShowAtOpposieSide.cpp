#include "ShowAtOpposieSide.h"
#include "Transform.h"
#include "Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

ShowAtOpposieSide::ShowAtOpposieSide()
{
}

ShowAtOpposieSide::~ShowAtOpposieSide()
{
}

void ShowAtOpposieSide::update()
{
	if (myTransform->getPos().getX() < (0 -myImage->getTexture().width())) {
		myTransform->getPos().setX(myTransform->getPos().getX() + sdlutils().width());
	}
	if (myTransform->getPos().getX() > sdlutils().width()) {
		myTransform->getPos().setX(myTransform->getPos().getX() - sdlutils().width());
	}
	if (myTransform->getPos().getY() < (0 - myImage->getTexture().height())) {
		myTransform->getPos().setY(myTransform->getPos().getY() + sdlutils().height());
	}
	if (myTransform->getPos().getY() > sdlutils().height()) {
		myTransform->getPos().setY(myTransform->getPos().getY() - sdlutils().height());
	}
}

void ShowAtOpposieSide::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	myImage = mngr_->getComponent<Image>(ent_);
}
