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
	if(ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_UP)) {


	}
}

void FighterCtrl::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);

	if (myTransform == nullptr) {
		throw "error, no se pudo obtener el componente transform";
	}

}
