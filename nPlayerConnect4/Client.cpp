#include "Client.h"

void Client::init()
{
	lobby.init();
}

int Client::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState, void(*winTitle)(std::string))
{
	if(currentState == GAME_END && mouseState == Game2D::KeyState::State::RELEASED){
		//if the player has clicked on the victory screen send them to the lobby
		currentState = LOBBY;
	}
	int result = -1;

	if(isConnected()){
		if(!incoming().empty()){
			auto msg = incoming().pop_front().msg;

			switch (msg.header.id) {
				case GameMsg::SERVER_CLOSE: {
					if(isConnected()){
						disconnect();
						return 1;//tell the engine to go back to the connect menu
					}
				}
				case GameMsg::SERVER_ACCEPT: {
					size_t size;
					msg >> size;

					for(int i = 0; i < size; i++){
						uint32_t id;
						Game2D::Colour colour;

						msg >> id;
						msg >> colour;

						lobby.setPlayerColour(id,colour);
					}

					uint32_t width, height;
					Game2D::Colour defaultColour;

					msg >> width;
					msg >> height;
					lobby.setBoardHeight(height);
					lobby.setBoardWidth(width);

					msg >> defaultColour;

					net::Message<GameMsg> outMsg;
					outMsg.header.id = GameMsg::PLAYER_COLOUR;
					outMsg << defaultColour;

					send(outMsg);
					//tell the server to tell every client what my colour is
					break;
				}
				case GameMsg::PLAYER_COLOUR: {
					Game2D::Colour colour;
					uint32_t id;
					msg >> id;
					msg >> colour;
					lobby.setPlayerColour(id, colour);
					break;
				}
				case GameMsg::CLIENT_DISCONNECT:{
					int id;
					msg>>id;
					lobby.removePlayer(id);
					break;
				}
				case GameMsg::BOARD_SIZE:{
					uint32_t width;
					uint32_t height;

					msg >> width;
					msg >> height;

					lobby.setBoardHeight(height);
					lobby.setBoardWidth(width);
					break;
				}
				case GameMsg::CONNECT_LENGTH:{
					uint32_t length;
					msg >> length;
					lobby.setConnectLength(length);
					break;
				}
				case GameMsg::GAME_START:{
					uint32_t noPlayers;
					uint32_t width, height;
					uint32_t connectLength;
					std::vector<Game2D::Colour> playerColours;
					msg >> noPlayers;

					for(int i = 0; i < noPlayers; i++){
						Game2D::Colour tempColour;
						msg >> tempColour;
						playerColours.push_back(tempColour);
					}
					//the colours where put pulled out in reverse order
					std::reverse(playerColours.begin(),playerColours.end());
					msg >> playerNo;
					msg >> width;
					msg >> height;
					msg >> connectLength;
					//set up the board
					board.setLineLength(connectLength);
					board.setBoardDims(width,height);
					board.setNumPlayers(noPlayers);
					board.setPlayerColours(playerColours);
					board.initBoard();

					if(winTitle){
						std::string tempStr = std::to_string(noPlayers);
						tempStr += " Player Connect ";
						tempStr += std::to_string(connectLength);
						winTitle(tempStr);
					}

					currentState = PLAYING;
					break;
				}
				case GameMsg::GAME_OVER:{
					if(winTitle){
						std::string tempStr = "n Player Connect x";
						winTitle(tempStr);
					}
					msg >> winningPlayer;
					lobby.setWinningPlayer(winningPlayer);
					if(winningPlayer == -2) {
						//client disconnected so return to lobby
						currentState = LOBBY;
					} else {
						currentState = GAME_END;
					}
					break;
				}
				case GameMsg::PLAYER_MOVE:{
					int32_t x, playerNum;
					unsigned int winningPlayer;
					msg >> playerNum;
					msg >> x;
					switch(board.makeMove(x,playerNum,winningPlayer)){
						case -1: {//board full
							net::Message<GameMsg> msg;
							msg.header.id = GameMsg::GAME_WIN;
							msg << (int32_t)-1;
							send(msg);
							break;
						}
						case 0: {//next player
							break;
						}
						case 1: {//player wins
							net::Message<GameMsg> msg;
							msg.header.id = GameMsg::GAME_WIN;
							msg << winningPlayer;
							send(msg);
							break;
						}
					}
					break;
				}
			}
		}
	} else {
		return 1;//go back
	}


	switch (currentState) {
		case LOBBY:
			result = lobby.processMouse(mousePos,mouseState);
			break;
		case PLAYING:
			if(board.getCurrentPlayer() == playerNo){
				unsigned int winningPlayer;
				int x;
				switch(board.processMouse(mousePos,mouseState,winningPlayer,&x)){
					case -2://no move made
						break;
					default:
						net::Message<GameMsg> msg;
						msg.header.id = GameMsg::PLAYER_MOVE;
						msg << (int32_t)x;
						msg << playerNo;
						send(msg);
						break;
				}
			}
			break;
	}


	switch (result) {
		case 2: {//player colour confirm button click
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::PLAYER_COLOUR;
			msg << lobby.getColour();
			send(msg);
			break;
		}
		case 3: {//start the game
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::GAME_START;
			msg << lobby.getConnectLength();
			msg << lobby.getBoardHeight();
			msg << lobby.getBoardWidth();
			send(msg);
			break;
		}
		case 5:{//connect length change
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::CONNECT_LENGTH;
			msg << lobby.getConnectLength();
			send(msg);
		}
		case 4: {//board size change
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::BOARD_SIZE;
			msg << lobby.getBoardHeight();
			msg << lobby.getBoardWidth();
			send(msg);
			break;
		}
		default:
			return result;
	}

	return -1;
}

void Client::draw()
{
	switch (currentState) {
		case LOBBY: {
			lobby.draw();
			break;
		}
		case PLAYING: {
			board.draw();
			Game2D::ScreenCoord::alignRight();
			float width = Game2D::Freetype::getLength(Game2D::Font::getFont(5), "You are Player %d", playerNo + 1);
			Game2D::Freetype::print(Game2D::Font::getFont(5), -width - 1, 44, "You are Player %d", playerNo + 1);
			Game2D::ScreenCoord::alignCentre();
			break;
		}
		case GAME_END: {
			board.draw();
			Game2D::Sprite tempSprite(Game2D::Rect(0, 0, 200, 200));
			tempSprite.setColour(Game2D::Colour(0, 0, 0, 0.5f));
			tempSprite.draw();
			Game2D::Colour::White.draw();
			if (winningPlayer == -1) {
				float width = Game2D::Freetype::getLength(Game2D::Font::getFont(5), "Tie");
				Game2D::Freetype::print(Game2D::Font::getFont(5), -width / 2.0, 35, "Tie");
			} else if (winningPlayer >= 0) {
				float width = Game2D::Freetype::getLength(Game2D::Font::getFont(5), "Player %d wins", winningPlayer + 1);
				Game2D::Freetype::print(Game2D::Font::getFont(5), -width / 2.0, 35, "Player %d wins", winningPlayer + 1);
			}
			float width = Game2D::Freetype::getLength(Game2D::Font::getFont(3), "Click to continue");
			Game2D::Freetype::print(Game2D::Font::getFont(3), -width/2.0f, 0, "Click to continue");
			break;
		}
	}
}