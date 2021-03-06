#ifndef SERVER_H
#define SERVER_H

#include <net.h>
#include "Message.h"
#include <Colour.h>
#include <map>
#include "Version.h"
#include <sstream>
#include <numeric>
#include <algorithm>
#include <random>

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
	virtual bool onClientConnect(std::shared_ptr<net::Connection<GameMsg>> client, net::Message<GameMsg>& denyMsg) override
	{
		//if the game has started reject the connection

		denyMsg.header.id = GameMsg::SERVER_DENY;

		std::string denyMsgStr = "Game in progress";
		if (inGame) {

			for (int i = denyMsgStr.size() - 1; i >= 0; i--) {
				denyMsg << denyMsgStr[i];
			}

			denyMsg << (uint8_t) denyMsgStr.size();

			return false;
		}

		//send the player their player number
		net::Message<GameMsg> msg;
		msg.header.id = GameMsg::SERVER_ACCEPT;

		msg << defaultPlayerColours.at(connCount++ % 9);

		msg << boardheight;
		msg << boardWidth;

		for (auto& it : playerColours) {
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
				bool gravity;

				msg >> width;
				msg >> height;
				msg >> connectLentgh;
				msg >> gravity;

				startGame(width,height,connectLentgh,gravity);
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
			case GameMsg::SERVER_DENY:{
				uint32_t playerId;
				msg >> playerId;

				net::Message<GameMsg> kickMsg;
				kickMsg.header.id = GameMsg::SERVER_DENY;

				std::string denyMsgStr = "You have been kicked";

				for (int i = denyMsgStr.size() - 1; i >= 0; i--) {
					kickMsg << denyMsgStr[i];
				}

				kickMsg << (uint8_t)denyMsgStr.size();

				for(auto& it : m_deqConnections) {
					if(it->getID() == playerId) {
						it->closeConnWithMsg(kickMsg);
					}
				}
			}
		}
	}

	virtual bool checkClient(net::Message<GameMsg> msg,bool& sendMsg, net::Message<GameMsg>& outMsg) override {
		sendMsg = true;//we'll close the connection
		Version temp;

		msg >> temp;

		//return (temp == GameVer);

		if(temp!=GameVer){
			//std::cout << "Rejecting\n";
			//net::Message<GameMsg> outMsg;
			outMsg.header.id = GameMsg::SERVER_DENY;
			std::string denyMsgStr;
			std::stringstream denyMsgStream;
			denyMsgStream << "Error incorrect game version (";
			denyMsgStream << GameVer;
			denyMsgStream << ") required";
			denyMsgStr = denyMsgStream.str();
			for (int i = denyMsgStr.size() - 1; i >= 0; i--) {
				outMsg << denyMsgStr[i];
			}

			outMsg << (uint8_t)denyMsgStr.size();
			//TODO send the incorrect game ver msg
			//client->closeConnWithMsg(outMsg);
			return false;
		}

		//bool grav;


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

	void startGame(uint32_t boardWidth, uint32_t boardHeight, uint32_t connectLength, bool gravity)
	{
		int i = 0;
		//generate random list of numbers
		std::vector<int32_t> playerOrder(m_deqConnections.size());//generate a vector the size of the amount of players
		std::iota(std::begin(playerOrder),std::end(playerOrder),0);//initalise list with acending numbers
		//std::random_shuffle(playerOrder.begin(),playerOrder.end());//randomise the player order
		std::shuffle(playerOrder.begin(), playerOrder.end(), std::default_random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
		for(auto& player : m_deqConnections){
			net::Message<GameMsg> msg;
			msg.header.id = GameMsg::GAME_START;
			//cast all the values to uint32 so they are the same size regardless of platform
			msg << gravity;
			msg << connectLength;
			msg << boardHeight;
			msg << boardWidth;
			msg << playerOrder.at(i++);//player number
			/*for(auto it : playerColours){
				msg << it.second;
			}*/
			for(auto it : playerOrder){
				msg << playerColours.at(m_deqConnections.at(it)->getID());
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
