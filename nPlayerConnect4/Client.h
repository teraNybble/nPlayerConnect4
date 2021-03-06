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
#include "TextureManager.h"
#include "PauseMenu.h"

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
	bool gravity;

	bool paused;
	PauseMenu pauseMenu;
protected:
public:
	virtual net::Message<GameMsg> sendClientCheck() override
	{
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::CLIENT_INFO;

		msg << GameVer;

		return msg;
	}

	void leave()
	{
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::CLIENT_DISCONNECT;
		send(msg);
	}

	void init();
	inline void reset() { currentState = LOBBY; lobby.reset(); }
	inline void resize() { board.resize(); }

	inline void processKeyboard(Game2D::KeyState::State escState) {
		if(escState == Game2D::KeyState::State::RELEASED){
			paused = !paused;
		}
	}
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);
	int processMessages(std::string& message,void(*winTitle)(std::string) = NULL);

	inline void setHost(bool host = false) { isHost = host; lobby.setHost(host); }
	inline void setGravity(bool grav) { gravity = grav; }

	Game2D::Colour getColour() const { return lobby.getColour(); }
	inline void setColour(Game2D::Colour colour) { lobby.setColour(colour); }

	void draw();
};


#endif //CLIENT_H
