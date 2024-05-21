#include "SafeSystem.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"

SafeSystem::SafeSystem()
{
}

SafeSystem::~SafeSystem()
{
}

void SafeSystem::initSystem()
{
}

void SafeSystem::update()
{
	checkIsSafe();
	updateSafeMode();
}

void SafeSystem::recieve(const Message& msg)
{
	 if (msg.id == _m_ENTER_SAFE_MODE) {
#ifdef _DEBUG
		std::cout << "enteerrrrrrr" << std::endl;
#endif // DEBUG

		safeMode = true;
		startSafeMode = sdlutils().virtualTimer().currTime();
	}
	else if (msg.id == _m_EXIT_SAFE_MODE) {
#ifdef _DEBUG
		std::cout << "exitttt" << std::endl;
#endif // DEBUG

		startTimeInDanger = sdlutils().virtualTimer().currTime();
		safeMode = false;
	}
}

void SafeSystem::checkIsSafe()
{
	if (safeMode) return;

	
	auto pacTf = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN));
	

	bool isIndanger = false;


	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {

		auto tf = mngr_->getComponent<Transform>(e);


		if ((tf->pos_ - pacTf->pos_).magnitude() < safeDistance) {
			isIndanger = true;
		}
	}

	if (!isIndanger) {
		startTimeInDanger = sdlutils().virtualTimer().currTime();
	}
	else if (startTimeInDanger + dangerTime <= sdlutils().virtualTimer().currTime()) {

		Message msg;
		msg.id = _m_ENTER_SAFE_MODE;

		mngr_->send(msg, true);


	}
}

void SafeSystem::updateSafeMode()
{

	if (!safeMode) return;


	if (startSafeMode + safeModeTime <= sdlutils().virtualTimer().currTime()) {

		Message msg;
		msg.id = _m_EXIT_SAFE_MODE;

		mngr_->send(msg, true);

	}
}
