#ifndef NET_SERVER_H
#define NET_SERVER_H

#include "net_common.h"
#include "net_TSQueue.h"
#include "net_message.h"
#include "net_connection.h"

namespace net
{
	template<typename T>
	class ServerInterface
	{
	private:
	protected:
		//incoming messages
		TSQueue<OwnedMessage<T>> m_qMessagesIn;

		//stores all active connections
		std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

		//order is important
		asio::io_context m_asioContext;
		std::thread m_threadContext;

		asio::ip::tcp::acceptor m_asioAcceptor;

		//UID for each client
		uint32_t nIDCounter = 100000;

		//called when client connects will disconnect the client if this function returns false
		virtual bool onClientConnect(std::shared_ptr<Connection<T>> client, Message<T>& denyMsg){
			return false;
		}

		virtual void onClientDisconnect(std::shared_ptr<Connection<T>> client){

		}

		virtual void onMessage(std::shared_ptr<Connection<T>> client, Message<T> msg){
		}
	public:
		ServerInterface(uint16_t port) : m_asioAcceptor(m_asioContext,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
		{
		}

		virtual ~ServerInterface(){
			stop();
		}

		bool start(){
			//restart the context if it has been stopped
			m_asioContext.restart();
			try{
				waitForClientConnect();
				m_threadContext = std::thread([this]() { m_asioContext.run(); });
			} catch (std::exception& e) {
				std::cerr << "[SERVER] Exception: " << e.what() << "\n";
				return false;
			}

			std::cout << "[SERVER] Started\n";
			return true;
		}

		void stop()	{
			m_asioContext.stop();

			if(m_threadContext.joinable()) { m_threadContext.join(); }

			//reset the counter
			//nIDCounter = 100000;
			//m_deqConnections.clear();
			//inform the user that the server has stopped
			std::cout << "[SERVER] Stopped\n";
		}

		virtual void onClientValidated(std::shared_ptr<Connection<T>> client){

		}

		//this is the function that can do things like ver checking (sendMsg is defaulted to false)
		virtual bool checkClient(Message<T> msg, bool& sendMsg,Message<T>& outMsg){
			return true;
		}

		//ASYNC
		void waitForClientConnect()	{
			m_asioAcceptor.async_accept(
				[this](std::error_code ec, asio::ip::tcp::socket socket){
					if(!ec){
						std::cout << "[SERVER] New connection: " << socket.remote_endpoint() << "\n";

						std::shared_ptr<Connection<T>> newConn =
								std::make_shared<Connection<T>>(Connection<T>::owner::SERVER,m_asioContext,
										std::move(socket), m_qMessagesIn);
						//gives the user the option of rejecting a connection

						Message<T> msg;

						if(onClientConnect(newConn, msg)){
							m_deqConnections.push_back(std::move(newConn));
							m_deqConnections.back()->connectToClient(this, nIDCounter++);

							std::cout << "[" << m_deqConnections.back()->getID() << "] Connection Approved\n";
						} else {
							m_deqConnections.push_back(std::move(newConn));
							m_deqConnections.back()->closeConnWithMsg(msg);
							std::cout << "[------] Connection Denied\n";
						}
					} else {
						std::cout << "[SERVER] New connection error: " << ec.message() << "\n";
					}

					waitForClientConnect();
				});
		}

		//send message to specified client
		void messageClient(std::shared_ptr<Connection<T>> client, const Message<T>& msg){
			//check client is connected
			if(client && client->isConnected()){
				client->send(msg);
			} else {
				//if the client isn't connected remove them
				onClientDisconnect(client);
				client.reset();
				m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(),client), m_deqConnections.end());
			}
		}

		//send message to all clients except the client specifed
		void messageAllClients(const Message<T> msg, std::shared_ptr<Connection<T>> ignoreClient = nullptr){
			bool invalidClientExists = false;

			for(auto& client : m_deqConnections){
				//cleck client is connected
				if(client && client->isConnected()){
					//if the client isn't being ignored
					if(client != ignoreClient){
						client->send(msg);
					}
				} else {
					//client isn't connected
					onClientDisconnect(client);
					client.reset();
					//there could be multiple invalid clients
					invalidClientExists = true;
				}
			}

			if(invalidClientExists){
				//remove all invalid contexts at once
				m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end());
			}
		}

		//default the max no of messages to uint max
		void update(size_t maxMessages = -1, bool wait = false){
			//std::cout << m_qMessagesIn.count() << "\n";
			if(wait) { m_qMessagesIn.wait(); }

			size_t messageCount = 0;

			//while we have messages and are still allowed to process messages
			while(messageCount < maxMessages && !m_qMessagesIn.empty()){
				//get the first message
				auto msg = m_qMessagesIn.pop_front();
				//pass to message handeler
				onMessage(msg.remote,msg.msg);
				messageCount++;
			}
		}
	};
}

#endif //NET_SERVER_H
