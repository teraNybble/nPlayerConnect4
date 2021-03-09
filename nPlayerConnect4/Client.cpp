#include "Client.h"

void Client::init()
{
	lobby.init();
}

int Client::processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState)
{
	int result = -1;

	//std::cout << (isConnected() ? "true" : "false") << "\n";

	if(isConnected()){
		if(!incoming().empty()){
			auto msg = incoming().pop_front().msg;

			switch (msg.header.id) {
				case GameMsg::SERVER_CLOSE: {
					std::cout << "serverClose\n";
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

					net::Message<GameMsg> outMsg;
					outMsg.header.id = GameMsg::PLAYER_COLOUR;
					outMsg << Game2D::Colour::Red;

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

					currentState = PLAYING;
					break;
				}
				case GameMsg::GAME_OVER:{
					int32_t winningPlayer;
					msg >> winningPlayer;
					lobby.setWinningPlayer(winningPlayer);
					currentState = LOBBY;
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
		case LOBBY:
			lobby.draw();
			break;
		case PLAYING:
			//freetype::print(Game2D::Font::getFont(5),0,35,"GAME!");
			board.draw();
			Game2D::ScreenCoord::alignRight();
			float width = freetype::getLength(Game2D::Font::getFont(5),"You are Player %d",playerNo+1);
			//TODO print out the text informing the user what player they are
			freetype::print(Game2D::Font::getFont(5),-width-1,44,"You are Player %d",playerNo+1);
			Game2D::ScreenCoord::alignCentre();
			break;

	}
}