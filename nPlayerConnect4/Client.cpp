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

	//std::cout << (isConnected() ? "true" : "false") << "\n";

	if(isConnected()){
		if(!incoming().empty()){
			auto msg = incoming().pop_front().msg;

			switch (msg.header.id) {
				case GameMsg::SERVER_CLOSE: {
					//std::cout << "serverClose\n";
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

					msg >> width;
					msg >> height;
					lobby.setBoardHeight(height);
					lobby.setBoardWidth(width);

					net::Message<GameMsg> outMsg;
					outMsg.header.id = GameMsg::PLAYER_COLOUR;
					outMsg << lobby.getColour();
					//outMsg << Game2D::Colour::Red;

					send(outMsg);
					//tell the server to tell every client what my colour is
					break;
				}
				case GameMsg::PLAYER_COLOUR: {
					//std::cout << "PlayerColour\n";
					Game2D::Colour colour;
					uint32_t id;
					msg >> id;
					msg >> colour;
					//std::cout << id << "\n";
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
				case GameMsg::GAME_START:{
					//int playerNumber;
					uint32_t noPlayers;
					uint32_t width, height;
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
					//set up the board
					board.setLineLength(4);
					board.setBoardDims(width,height);
					board.setNumPlayers(noPlayers);
					board.setPlayerColours(playerColours);
					board.initBoard();

					if(winTitle){
						std::string tempStr = std::to_string(noPlayers);
						tempStr += " Player Connect ";
						tempStr += std::to_string(4);
						winTitle(tempStr);
					}

					currentState = PLAYING;
					break;
				}
				case GameMsg::GAME_OVER:{
					if(winTitle){
						//std::string tempStr = std::to_string(noPlayers);
						std::string tempStr = "n Player Connect 4";
						winTitle(tempStr);
					}
					//int32_t winningPlayer;
					msg >> winningPlayer;
					lobby.setWinningPlayer(winningPlayer);
					currentState = GAME_END;
					break;
				}
				case GameMsg::PLAYER_MOVE:{
					//std::cout << "PlayerMove\n";
					int32_t x, playerNum;
					unsigned int winningPlayer;
					msg >> playerNum;
					msg >> x;
					switch(board.makeMove(x,playerNum,winningPlayer)){
						case -1: {//board full
							//std::cout << "Case -1\n";
							net::Message<GameMsg> msg;
							msg.header.id = GameMsg::GAME_WIN;
							msg << (int32_t)-1;
							send(msg);
							break;
						}
						case 0: {//next player
							//std::cout << "Case 0\n";
							break;
						}
						case 1: {//player wins
							//std::cout << "Case 1\n";
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

	/*
	if(board.getCurrentPlayer() == playerNo){
		//TODO do a move and send it
		unsigned int winningPlayer;
		int x;
		switch(board.processMouse(mousePos,mouseState,winningPlayer,&x)){
			default:
				net::Message<GameMsg> msg;
				msg.header.id = GameMsg::PLAYER_MOVE;
				msg << (int32_t)x;
				msg << playerNo;
				send(msg);
				break;
		}
	}*/


	switch (currentState) {
		case LOBBY:
			result = lobby.processMouse(mousePos,mouseState);
			break;
		case PLAYING:
			if(board.getCurrentPlayer() == playerNo){
				//TODO do a move and send it
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
		case 2: {//test button click
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::PLAYER_COLOUR;
			msg << lobby.getColour();
			send(msg);
			break;
		}
		case 3: {//start the game
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::GAME_START;
			msg << lobby.getBoardHeight();
			msg << lobby.getBoardWidth();
			send(msg);
			break;
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

	//return lobby.processMouse(mousePos,mouseState);

	return -1;
}

void Client::draw()
{
	//freetype::print(Game2D::Font::getFont(5),0,35,"GAME!");
	switch (currentState) {
		case LOBBY: {
			lobby.draw();
			break;
		}
		case PLAYING: {
			//freetype::print(Game2D::Font::getFont(5),0,35,"GAME!");
			board.draw();
			Game2D::ScreenCoord::alignRight();
			float width = freetype::getLength(Game2D::Font::getFont(5), "You are Player %d", playerNo + 1);
			//TODO print out the text informing the user what player they are
			freetype::print(Game2D::Font::getFont(5), -width - 1, 44, "You are Player %d", playerNo + 1);
			Game2D::ScreenCoord::alignCentre();
			break;
		}
		case GAME_END: {
			board.draw();
			Game2D::Sprite tempSprite(Game2D::Rect(0, 0, 200, 200));
			tempSprite.setColour(Game2D::Colour(0, 0, 0, 0.5f));
			tempSprite.draw();
			//std::cout << winningPlayer << "\n";
			Game2D::Colour::White.draw();
			if (winningPlayer == -1) {
				float width = freetype::getLength(Game2D::Font::getFont(5), "Tie");
				freetype::print(Game2D::Font::getFont(5), -width / 2.0, 35, "Tie");
			} else if (winningPlayer >= 0) {
				float width = freetype::getLength(Game2D::Font::getFont(5), "Player %d wins", winningPlayer + 1);
				freetype::print(Game2D::Font::getFont(5), -width / 2.0, 35, "Player %d wins", winningPlayer + 1);
			}
			float width = freetype::getLength(Game2D::Font::getFont(3), "Click to continue");
			freetype::print(Game2D::Font::getFont(3), -width/2.0f, 0, "Click to continue");
			break;
		}
	}
}