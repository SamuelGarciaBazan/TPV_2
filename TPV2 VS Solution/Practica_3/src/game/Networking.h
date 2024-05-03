// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "netwrok_messages.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(const char *host, Uint16 port,std::string& name);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return clientId_;
	}

	bool is_master() {
		return clientId_ == masterId_;
	}



	void send_my_info(const Vector2D &pos,const Vector2D &vel ,float speed, float acceleration ,float theta,
			Uint8 state,float life);

	void send_syncro_info(int clientId, const Vector2D& pos);

	void send_shoot_request();

	void send_player_die(int playerID);

	void send_waiting_msg();

	void send_new_start();

	void send_player_hit(int idLifes,int idPoints, int life, int points);

	void send_player_name(int id, std::string name);

private:

	void handle_new_client(Uint8 id);

	void handle_disconnet(Uint8 id);

	void handle_player_info(const PlayerInfoMsg &m);

	void handle_syncro_info(const SyncroMsg& m);

	void handle_shoot_request(const MsgWithId& m);

	void handle_player_die(const PlayerDieMsg& m);
	
	void handle_start_waiting();

	void handle_new_start();

	void handle_player_hit(const PlayerHit& m);

	void handle_player_name(PlayerName& m);


	UDPsocket sock_;
	SDLNet_SocketSet socketSet_;
	UDPpacket *p_;
	IPaddress srvadd_;
	Uint8 clientId_;
	Uint8 masterId_;



	void string_to_chars(std::string& str, char c_str[11]);

	void chars_to_string(std::string& str, char c_str[11]);
};

