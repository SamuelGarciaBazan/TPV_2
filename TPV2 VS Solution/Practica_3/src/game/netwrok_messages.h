// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"

enum MsgType : Uint8 {
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECTED,
	_NEW_CLIENT_CONNECTED, //
	_PLAYER_INFO, //
	_SYNCRO,
	_SHOOT_REQUEST,
	_PLAYER_DIE,
	_START_WAITING,
	_NEW_START,
	_PLAYER_HIT,
	_PLAYER_NAME
};

struct Msg {

	Msg() {};
	Msg(Uint8 _type) : _type(_type) {};

	Uint8 _type;

	_IMPL_SERIALIAZION_(_type)
};

struct MsgWithId: Msg {
	
	MsgWithId() {};
	MsgWithId(Uint8 _type, Uint8 _client_id)
		:Msg(_type), _client_id(_client_id) {};

	Uint8 _client_id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,_client_id)
};

struct MsgWithMasterId: MsgWithId {

	MsgWithMasterId() {};
	MsgWithMasterId(Uint8 _type, Uint8 _client_id, Uint8 _master_id)
		:MsgWithId(_type, _client_id), _master_id(_master_id) {};

	Uint8 _master_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,_master_id)
};


struct PlayerInfoMsg: MsgWithId {

	float posX;
	float posY;
	float velX;
	float velY;
	float speed;
	float acceleration;
	float theta;
	float life;
	Uint8 state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,
		posX, posY, velX, velY,
		speed, acceleration, theta,life, state);

};
struct ShootMsg: MsgWithId {

	float x;
	float y;
	float vx;
	float vy;
	int w;
	int h;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,vx,vy,w,h,rot)

};


struct SyncroMsg : MsgWithId {

	float posX;
	float posY;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,posX,posY)
};

struct PlayerDieMsg : MsgWithId {

	int playerDie;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,playerDie)
};

struct PlayerHit : Msg {

	int id_life;
	int id_points;
	int currentLife;
	int currentPoints;


	_IMPL_SERIALIAZION_WITH_BASE_(Msg, id_life, id_points,currentLife,currentPoints)
};


struct PlayerName : Msg {

	int id;

	char name[11];

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,id, name, 11u);

};