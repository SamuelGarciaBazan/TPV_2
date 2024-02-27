#include "Image.h"
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Manager.h"




Image::Image(std::string key)
{
	myTexture =  &sdlutils().instance()->images().at(key);
}

Image::~Image()
{
}

void Image::render()
{
	myTexture->render(build_sdlrect(myTransform->getPos(), myTexture->width(), myTexture->height()));	
}

void Image::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	
	if (myTransform == nullptr) {
		throw "error, no se pudo obtener el componente transform";
	}
}

