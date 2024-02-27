#include "FighterCtrl.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"


FighterCtrl::FighterCtrl()
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::update()
{
	if(ih().keyDownEvent()) {
		//acelaration
		if (ih().isKeyDown(SDL_SCANCODE_UP)) {
			myTransform->getVel().set(myTransform->getVel() + Vector2D(0, -1).rotate(myTransform->getRot() ) * thrust);
			if (myTransform->getVel().magnitude() > speedLimit) {
				myTransform->getVel().set(myTransform->getVel().normalize() * speedLimit);
			}
		}		
		else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {//rotation
			myTransform->setRot(myTransform->getRot() - rotationRate);
		}
		else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {//rotation
			myTransform->setRot(myTransform->getRot() + rotationRate);
		}

	}
}

void FighterCtrl::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);

	if (myTransform == nullptr) {
		throw "error, no se pudo obtener el componente transform";
	}
	
}
