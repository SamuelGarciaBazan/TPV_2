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
			myTransform->getVel().set(myTransform->getVel() + Vector2D(0, -1).rotate(myTransform->getRot() * thrust));
		}		
		else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {//rotation

		}
		else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {//rotation

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
