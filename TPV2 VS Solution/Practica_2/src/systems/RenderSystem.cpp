#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../sdlutils/SDLUtils.h"


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::initSystem()
{
}

void RenderSystem::update()
{
	renderFruits();
	renderGhosts();
	renderPacman();
}

void RenderSystem::recieve(const Message&)
{
}

void RenderSystem::renderFruits()
{
}

void RenderSystem::renderGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto img = mngr_->getComponent<ImageWithFrames>(e);

		updateImageWithFrames(img);
		renderImageWithFrames(img);
	}

}

void RenderSystem::renderPacman()
{
	auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto img = mngr_->getComponent<ImageWithFrames>(pacMan);

	updateImageWithFrames(img);
	renderImageWithFrames(img);
	
	renderLifes();
}

void RenderSystem::renderLifes()
{
	auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto healthCmp = mngr_->getComponent<Health>(pacMan);

	healthCmp->render();//cambiar para evitar llamada a metodos virtuales
}

void RenderSystem::renderImageWithFrames(ImageWithFrames* img)
{
	
	img->myTexture->render(build_sdlrect((img->currentFrame % img->cols) * img->frameWidth, (img->currentFrame / img->cols) * img->frameHeight, img->frameWidth, img->frameHeight),
		build_sdlrect(img->myTransform->getPos(), img->myTransform->getWidth(), img->myTransform->getHeight()), img->myTransform->getRot());

}

void RenderSystem::updateImageWithFrames(ImageWithFrames* img)
{
	if ((img->lastFrame + img->frameTime) < sdlutils().virtualTimer().currTime()) {

		img->lastFrame = sdlutils().virtualTimer().currTime();
		img->currentFrame++;
		if (img->currentFrame > img->lastIndex) {
			img->currentFrame = img->firstIndex;
		}
	}

}
