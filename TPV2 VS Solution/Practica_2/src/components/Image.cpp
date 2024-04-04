#include "Image.h"
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Manager.h"




Image::Image(std::string id, int fils, int cols)
	:fils(fils), cols(cols)
{
	myTexture = &sdlutils().images().at(id);

	frameWidth = myTexture->width() / cols;
	frameHeight = myTexture->height() / fils;
}

Image::~Image()
{
}

void Image::render()
{
	myTexture->render(build_sdlrect(myTransform->getPos(), myTransform->getWidth(), myTransform->getHeight()),myTransform->getRot());	
}

void Image::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	
	assert(myTransform != nullptr);
}

