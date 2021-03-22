#ifndef SERVER_H
#define SERVER_H

#include <net.h>
#include "Message.h"
#include <Colour.h>
#include <map>
#include "Version.h"

class Server : public net::ServerInterface<GameMsg>
{
private:
	std::string password;
	bool inGame;
	uint32_t boardWidth;
	uint32_t boardheight;
	//Version serverVer;
	std::map<uint32_t,Game2D::Colour> playerColours;
	std::vector<uint32_t> garbageIDs;
	unsigned int connCount;

	std::vector<Game2D::Colour> defaultPlayerColours = {
			Game2D::Colour::Red, Game2D::Colour::Yellow,
			Game2D::Colour::Green, Game2D::Colour::Blue,
			Game2D::Colour::Cyan, Game2D::Colour::Magenta,
			Game2D::Colour::White, Game2D::Colour(1,0.65f,0),
			Game2D::Colour(1,0.75f,0.8f),
	};
protected:
	virtual bool onClientConnect(std::shared_ptr<net::Connection<GameMsg>> client) override {

	//if the game has started reject the connection
	if(inGame){
		return false;
	}

		//send the player their player number
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::SERVER_ACCEPT;

		msg << defaultPlayerColours.at(connCount++ % 9);

		msg << boardheight;
		msg << boardWidth;

		for(auto& it : playerColours){
			//push the colour then the ID
			msg << it.second << it.first;
		}
		//push the size last so the user can get the size
		msg << playerColours.size();

		client->send(msg);

		return true;
	}
	virtual void onClientDisconnect(std::shared_ptr<net::Connection<GameMsg>> client) override{
		if(client) {
			if(!(playerColours.find(client->getID()) == playerColours.end())){
				auto& pd = playerColours[client->getID()];
				playerColours.erase(client->getID());
				garbageIDs.push_back(client->getID());
			}
		}
	}
	virtual void onMessage(std::shared_ptr<net::Connection<GameMsg>> client, net::Message<GameMsg> msg) override {
		switch (msg.header.id){
			case GameMsg::PLAYER_COLOUR: {
				//send the player colour to all clients sans the sending client
				Game2D::Colour playerColour;
				msg >> playerColour;//get the colour from the message
				net::Message<GameMsg> outMsg;

				//add the player and colour to the list
				std::pair<std::map<uint32_t,Game2D::Colour>::iterator,bool> ret;
				ret = playerColours.insert(std::pair<uint32_t,Game2D::Colour>(client->getID(),playerColour));
				//if the insert function returned false the player already exsists
				if(!ret.second){
					//update player colour
					ret.first->second = playerColour;
				}

				outMsg.header.id = GameMsg::PLAYER_COLOUR;
				outMsg << playerColour;//send the colour and the id to the clients
				outMsg << client->getID();
				messageAllClients(outMsg);
				break;
			}
			case GameMsg::BOARD_SIZE:{
				//send the board size to everyone except the sending client
				msg >> boardWidth;
				msg >> boardheight;

				net::Message<GameMsg> outMsg;
				outMsg.header.id = GameMsg::BOARD_SIZE;
				outMsg << boardheight;
				outMsg << boardWidth;

				messageAllClients(outMsg,client);
				break;
			}
			case GameMsg::CONNECT_LENGTH:{
				messageAllClients(msg,client);
				break;
			}
			case GameMsg::PLAYER_MOVE: {
				//send the move to everyone except the sending client
				messageAllClients(msg,client);
				break;
			}
			case GameMsg::GAME_START:{
				uint32_t width;
				uint32_t height;
				uint32_t connectLentgh;

				msg >> width;
				msg >> height;
				msg >> connectLentgh;

				startGame(width,height,connectLentgh);
				break;
			}
			case GameMsg::GAME_WIN: {
				//inform all the clients who won
				msg.header.id = GameMsg::GAME_OVER;
				messageAllClients(msg);
				inGame = false;
				break;
			}
			case GameMsg::CLIENT_DISCONNECT: {
				if(!(playerColours.find(client->getID()) == playerColours.end())){
					auto& pd = playerColours[client->getID()];
					playerColours.erase(client->getID());
					garbageIDs.push_back(client->getID());
				}
				break;
			}
		}
	}

	virtual bool checkClient(net::Message<GameMsg> msg, std::shared_ptr<net::Connection<GameMsg>> client) override {
		Version temp;

		msg >> temp;

		return (temp == GameVer);

		return true;
	}
public:
	Server(uint16_t port) : net::ServerInterface<GameMsg>(port){
		boardWidth = 7;
		boardheight = 6;
		connCount = 0;
	}

	~Server(){
		m_qMessagesIn.wake_up();
#if _WIN32
		m_deqConnections.clear();
		//std::cout << "Cleard the deq\n";
#endif
	}

	void startGame(uint32_t boardWidth, uint32_t boardHeight, uint32_t connectLength)
	{
		int i = 0;
		for(auto& player : m_deqConnections){
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::GAME_START;
			//cast all the values to uint32 so they are the same size regardless of platform
			msg << connectLength;
			msg << boardHeight;
			msg << boardWidth;
			msg << (int32_t)i++;//player number
			for(auto it : playerColours){
				msg << it.second;
			}
			msg << (uint32_t)playerColours.size();
			player->send(msg);
		}

		inGame = true;
	}

	void heartBeat(){
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::HEART_BEAT;

		messageAllClients(msg);

		//go through all the disconnected clients and inform the remaining clients to remove them
		if(!garbageIDs.empty()){
			for(auto pid : garbageIDs){
				if(inGame){
					//if we are in a game stop the game as someone has left
					net::Message<GameMsg> outMsg;
					outMsg.header.id = GameMsg::GAME_OVER;
					outMsg << -2;
					messageAllClients(outMsg);
					inGame = false;
				}
				net::Message<GameMsg> m;
				m.header.id = GameMsg::CLIENT_DISCONNECT;
				m << pid;
				messageAllClients(m);
			}
			garbageIDs.clear();
		}
	}
};


#endif //SERVER_H
