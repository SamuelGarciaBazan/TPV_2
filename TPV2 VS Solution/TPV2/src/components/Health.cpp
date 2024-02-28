#include "Health.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

Health::Health(std::string name)
{
	healthTexture = &sdlutils().images().at(name);

}

Health::~Health()
{
}

void Health::render()
{
	Vector2D pos(0, 0);
	
	healthTexture->render(build_sdlrect(pos, healthTexture->width(), healthTexture->height()));
}
