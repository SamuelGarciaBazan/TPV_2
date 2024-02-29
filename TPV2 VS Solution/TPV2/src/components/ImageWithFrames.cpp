#include "ImageWithFrames.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"



ImageWithFrames::ImageWithFrames(std::string id, int fils, int cols)
	:fils(fils),cols(cols)
{
	myTexture = &sdlutils().images().at(id);

}

ImageWithFrames::~ImageWithFrames()
{
}

void ImageWithFrames::update()
{
}
