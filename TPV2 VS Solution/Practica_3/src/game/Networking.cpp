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

bool Networking::init(const char *host, Uint16 port,std::string& name) {

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

	std::cin >> name;

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
	MsgWithId m(_DISCONNECTED,clientId_);

	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);
}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
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

		case _PLAYER_INFO:
			//std::cout << "Recived message with type: _PLAYER_INFO" << std::endl;

			m5.deserialize(p_->data);
			handle_player_info(m5);
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
		case _PLAYER_HIT: {

			PlayerHit m;
			m.deserialize(p_->data);			
			handle_player_hit(m);
			break;
		}
		case _PLAYER_NAME: {

			PlayerName m;
			m.deserialize(p_->data);
			handle_player_name(m);
			break;
		}
		default:
			break;
		}
	}
}

#pragma region Handle methods


void Networking::handle_new_client(Uint8 id) {
	if (id != clientId_) {
		Game::instance()->getLittleWolf()->send_my_info();
		Game::instance()->getLittleWolf()->send_Info_Points();
		Game::instance()->getLittleWolf()->send_my_name();
	}
}

void Networking::handle_disconnet(Uint8 id) {
	Game::instance()->getLittleWolf()->disconnet_player(id);
}

void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != clientId_) {
		//std::cout << "Recived info from other player" << std::endl;
		
		Game::instance()->getLittleWolf()->update_player_info(
		m._client_id, m.posX, m.posY, m.velX, m.velY,
		m.speed, m.acceleration, m.theta, (LittleWolf::PlayerState)m.state,m.life);
	}
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

void Networking::handle_player_hit(const PlayerHit& m)
{
	Game::instance()->getLittleWolf()->proccess_player_hit(m.id_life,m.id_points,m.currentLife,m.currentPoints);
}

void Networking::handle_player_name(PlayerName& m)
{
	std::string name;

	chars_to_string(name, m.name);

	Game::instance()->getLittleWolf()->setName(m.id, name);
}

#pragma endregion

#pragma region Conversiom string <-> chars

void Networking::string_to_chars(std::string& str, char c_str[11])
{
	auto i = 0u;
	for (; i < str.size() && i < 10; i++) c_str[i] = str[i];
	c_str[i] = 0;
}

void Networking::chars_to_string(std::string& str, char c_str[11])
{
	c_str[10] = 0;
	str = std::string(c_str);
}

#pragma endregion

#pragma region Send Methods

void Networking::send_my_info(const Vector2D& pos, const Vector2D& vel,
	float speed, float acceleration, float theta,
	Uint8 state, float life)
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
	m.life = life;

	//send message
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
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
	MsgWithId m(_SHOOT_REQUEST,clientId_);

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
	Msg m(_START_WAITING);

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_new_start()
{
	Msg m(_NEW_START);

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_player_hit(int idLife,int idPoints, int life, int points)
{
	PlayerHit m;

	m._type = _PLAYER_HIT;
	m.id_life = idLife;
	m.id_points = idPoints;
	m.currentLife = life;
	m.currentPoints = points;

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_player_name(int id, std::string name)
{
	PlayerName m;

	m._type = _PLAYER_NAME;
	m.id = id;

	string_to_chars(name, m.name);

	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

#pragma endregion
