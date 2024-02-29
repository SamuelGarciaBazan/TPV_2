#include "FighterCtrl.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"


FighterCtrl::FighterCtrl()
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::update()
{

	//acelaration
	if (ih().isKeyDown(SDL_SCANCODE_UP)) {
		sdlutils().soundEffects().at("thrust").play();
		myTransform->getVel().set(myTransform->getVel() + Vector2D(0, -1).rotate(myTransform->getRot() ) * thrust);
		if (myTransform->getVel().magnitude() > speedLimit) {
			myTransform->getVel().set(myTransform->getVel().normalize() * speedLimit);
		}
	}		
	if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {//rotation
		myTransform->setRot(myTransform->getRot() - rotationRate);
	}
	if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {//rotation
		myTransform->setRot(myTransform->getRot() + rotationRate);
	}

	
}

void FighterCtrl::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);

	assert(myTransform != nullptr);
}
