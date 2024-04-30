// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>
#include "../utils/Vector2D.h"

#include "Game.h"
#include "netwrok_messages.h"
#include "../sdlutils/SDLNetUtils.h"

#include "LittleWolf.h"

Networking::Networking() :
		sock_(), //
		socketSet_(), //
		p_(), //
		srvadd_(), //
		clientId_(), //
		masterId_() {
}

Networking::~Networking() {
}

bool Networking::init(const char *host, Uint16 port) {

	if (SDLNet_ResolveHost(&srvadd_, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sock_ = SDLNet_UDP_Open(0);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet_, sock_);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					std::cout << "Recived message with type: _CONNECTION_ACCEPTED" << std::endl;

					m1.deserialize(p_->data);
					clientId_ = m1._client_id;
					masterId_ = m1._master_id;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					std::cout << "Recived message with type: _CONNECTION_REJECTED" << std::endl;

					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int) clientId_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = clientId_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	MsgWithId m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			std::cout << "Recived message with type: _NEW_CLIENT_CONNECTED" << std::endl;

			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			std::cout << "Recived message with type: _DISCONNECTED" << std::endl;

			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			std::cout << "Recived message with type: _PLAYER_STATE" << std::endl;

			m2.deserialize(p_->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			//std::cout << "Recived message with type: _PLAYER_INFO" << std::endl;

			m5.deserialize(p_->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			std::cout << "Recived message with type: _SHOOT" << std::endl;

			m3.deserialize(p_->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			std::cout << "Recived message with type: _DEAD" << std::endl;


			m4.deserialize(p_->data);
			handle_dead(m4);
			break;

		case _RESTART:
			std::cout << "Recived message with type: _RESTART" << std::endl;

			handle_restart();
			break;

		case _SYNCRO: {

			std::cout << "Recived message with type: _SYNCRO" << std::endl;
			SyncroMsg m;
			m.deserialize(p_->data);


			handle_syncro_info(m);
			break;
		}
		case _SHOOT_REQUEST: {

			std::cout << "Recived message with type: _SHOOT_REQUEST" << std::endl;

			MsgWithId m;
			m.deserialize(p_->data);

			handle_shoot_request(m);

			break;
		}
		case _PLAYER_DIE: {
			std::cout << "Recived message with type: _PLAYER_DIE" << std::endl;

			PlayerDieMsg m;
			m.deserialize(p_->data);

			handle_player_die(m);
			
			break;
		}
		case _START_WAITING: {
			std::cout << "Recived message with type: _START_WAITING" << std::endl;

			handle_start_waiting();


			break;
		}
		case _NEW_START: {

			handle_new_start();

			break;
		}

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != clientId_)
		Game::instance()->getLittleWolf()->send_my_info();
}

void Networking::handle_disconnet(Uint8 id) {
	Game::instance()->getLittleWolf()->disconnet_player(id);
	//Game::instance()->get_fighters().removePlayer(id);
}

void Networking::send_state(const Vector2D &pos, float w, float h, float rot) {
	PlayerStateMsg m;
	m._type = _PLAYER_STATE;
	m._client_id = clientId_;
	m.x = pos.getX();
	m.y = pos.getY();
	m.w = w;
	m.h = h;
	m.rot = rot;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {

	if (m._client_id != clientId_) {
		//Game::instance()->get_fighters().update_player_state(m._client_id, m.x,
			//	m.y, m.w, m.h, m.rot);
	}
}

void Networking::send_shoot(Vector2D p, Vector2D v, int width, int height,
		float r) {
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = clientId_;
	m.x = p.getX();
	m.y = p.getY();
	m.vx = v.getX();
	m.vy = v.getY();
	m.w = width;
	m.h = height;
	m.rot = r;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_shoot(const ShootMsg &m) {
	//Game::instance()->get_bullets().shoot(Vector2D(m.x, m.y),
		//	Vector2D(m.vx, m.vy), m.w, m.h, m.rot);

}

void Networking::send_dead(Uint8 id) {
	MsgWithId m;
	m._type = _DEAD;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_dead(const MsgWithId &m) {
	//Game::instance()->get_fighters().killPlayer(m._client_id);
}

void Networking::send_my_info(	const Vector2D& pos, const Vector2D& vel,
								float speed, float acceleration, float theta,
								Uint8 state) 
{
	PlayerInfoMsg m; 
	//id && type of message
	m._client_id = clientId_;
	m._type = _PLAYER_INFO;

	//info player
	m.posX = pos.getX();
	m.posY = pos.getY();
	m.velX = vel.getX();
	m.velY = vel.getY();
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;

	//send message
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}


void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != clientId_) {
		//std::cout << "Recived info from other player" << std::endl;
		

		Game::instance()->getLittleWolf()->update_player_info(
		m._client_id, m.posX, m.posY, m.velX, m.velY,
		m.speed, m.acceleration, m.theta, (LittleWolf::PlayerState)m.state);
	}
}

void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_restart() {
	//Game::instance()->get_fighters().bringAllToLife();

}

void Networking::handle_syncro_info(const SyncroMsg& m)
{
	Game::instance()->getLittleWolf()->update_syncro_info(m._client_id,Vector2D(m.posX,m.posY));
}

void Networking::handle_shoot_request(const MsgWithId& m)
{
	if (is_master()) {

		std::cout << "Master process shoot" << std::endl;

		Game::instance()->getLittleWolf()->proccess_shoot_request(m._client_id);
	}
}

void Networking::handle_player_die(const PlayerDieMsg& m)
{
	if (m._client_id != clientId_) {
		Game::instance()->getLittleWolf()->proccess_player_die(m.playerDie);
	}

}

void Networking::handle_start_waiting()
{
	Game::instance()->getLittleWolf()->process_wainting_msg();
}

void Networking::handle_new_start()
{
	Game::instance()->getLittleWolf()->proccess_new_start();
}


void Networking::send_syncro_info(int clientId, const Vector2D& pos)
{
	SyncroMsg m;

	m._client_id = clientId;
	m._type = _SYNCRO;

	m.posX = pos.getX();
	m.posY = pos.getY();

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);

}

void Networking::send_shoot_request()
{
	MsgWithId m;
	m._client_id = clientId_;
	m._type = _SHOOT_REQUEST;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_player_die(int playerID)
{

	PlayerDieMsg m;
	m._client_id = clientId_;
	m.playerDie = playerID;
	m._type = _PLAYER_DIE;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);

}

void Networking::send_waiting_msg()
{
	Msg m;

	m._type = _START_WAITING;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_new_start()
{
	Msg m;

	m._type = _NEW_START;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}
