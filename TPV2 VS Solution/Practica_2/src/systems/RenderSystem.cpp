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

void RenderSystem::recieve(const Message& msg)
{
	if (msg.id == _m_IMMUNITY_START) {
		immunityStart();
	}
	else if (msg.id == _m_IMMUNITY_END) {
		immunityEnd();
	}
}

void RenderSystem::renderFruits()
{
}

void RenderSystem::renderGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto img = mngr_->getComponent<ImageWithFrames>(e);

		if (!pacManImmune) {
			updateImageWithFrames(img);
		}
		else {
			updateGhostsImmunityON(img);
		}
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

	Vector2D pos;
	for (int i = 0; i < healthCmp->currentLifes; i++) {
		pos.set(healthCmp->initialX + (healthCmp->offSetX * i), healthCmp->initialY);
		healthCmp->healthTexture->render(build_sdlrect(pos, healthCmp->healthTexture->width() * healthCmp->scale, healthCmp->healthTexture->height() * healthCmp->scale));
	}
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

void RenderSystem::updateGhostsImmunityON(ImageWithFrames* img)
{

	if ((img->lastFrame + img->frameTime) < sdlutils().virtualTimer().currTime()) {

		img->lastFrame = sdlutils().virtualTimer().currTime();
		img->currentFrame++;
		if (img->currentFrame >lastIndexImmunityGhost) {
			img->currentFrame = firstIndexImmunityGhost;
		}
	}
}

void RenderSystem::immunityStart()
{
	pacManImmune = true;

	//setear el frame a fantasma asustado de manera aleatoria
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto img = mngr_->getComponent<ImageWithFrames>(e);

		int rand = sdlutils().rand().nextInt(0, 2);

		img->currentFrame = rand == 0 ? firstIndexImmunityGhost : lastIndexImmunityGhost;

	}
}

void RenderSystem::immunityEnd()
{
	pacManImmune = false;

	//devolver el frame a su sitio correspondiente, de manera aleatoriaa
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {

		auto img = mngr_->getComponent<ImageWithFrames>(e);

		int rand = sdlutils().rand().nextInt(0, 8);

		img->currentFrame = img->firstIndex + rand;

	}
}
