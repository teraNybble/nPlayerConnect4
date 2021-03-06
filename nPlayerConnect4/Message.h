#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>

enum class GameMsg : uint32_t
{
	HEART_BEAT,
	CLIENT_INFO,
	CLIENT_DISCONNECT,
	SERVER_ACCEPT,
	SERVER_DENY,
	SERVER_CLOSE,
	PLAYER_MOVE,
	PLAYER_COLOUR,
	BOARD_SIZE,
	CONNECT_LENGTH,
	GAME_START,
	GAME_WIN,
	GAME_TIE,
	GAME_OVER
};

#endif //MESSAGE_H
