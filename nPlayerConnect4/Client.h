#ifndef CLIENT_H
#define CLIENT_H

#include <net.h>
#include "Message.h"
#include <freetype.h>
#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include <ScreenCoord.h>
#include "FontInfo.h"
#include "Lobby.h"
#include "Board.h"
#include <algorithm>
#include "Version.h"

class Client : public net::ClientInterface<GameMsg>
{
private:
	enum State { LOBBY, PLAYING, GAME_END };
private:
	Lobby lobby;
	Board board;

	bool isHost;
	State currentState;
	int32_t playerNo;
	int32_t winningPlayer;
protected:
public:
	virtual net::Message<GameMsg> sendClientCheck() override
	{
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::CLIENT_INFO;

		msg << GameVer;

		return msg;
	}

	void init();
	inline void reset() { currentState = LOBBY; lobby.reset(); }

	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);

	inline void setHost(bool host = false) { isHost = host; lobby.setHost(host); }

	inline Game2D::Colour getColour() const { return lobby.getColour(); }
	inline void setColour(Game2D::Colour colour) { lobby.setColour(colour); }

	void draw();
};


#endif //CLIENT_H
