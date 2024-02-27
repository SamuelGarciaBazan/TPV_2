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
	myTexture->render(build_sdlrect(myTransform->getPos(), myTexture->width(), myTexture->height()),myTransform->getRot());	
}

void Image::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	
	assert(myTransform != nullptr);
}

