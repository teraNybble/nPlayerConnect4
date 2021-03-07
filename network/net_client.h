#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include "net_common.h"
#include "net_TSQueue.h"
#include "net_message.h"
#include "net_connection.h"


namespace net
{
	template<typename T>
	class ClientInterface
	{
	private:
		TSQueue<OwnedMessage<T>> m_QMessagesIn;
	protected:
		asio::io_context m_context;
		std::thread thrContext;
		asio::ip::tcp::socket m_socket;
		std::unique_ptr<Connection<T>> m_connection;

		//called when connected to the server
		virtual void onServerConnect() {}


	public:
		ClientInterface() : m_socket(m_context){

		}

		virtual ~ClientInterface(){
			disconnect();
		}

		virtual Message<T> sendClientCheck() { 
#ifdef _WIN32
			return Message<T>();
#endif // _WIN32

		}

		bool connect(const std::string& host, const uint16_t port){
			try{
				//resolve hostname/ip
				asio::ip::tcp::resolver resolver(m_context);
				asio::ip::tcp::resolver::results_type m_endpoints = resolver.resolve(host,std::to_string(port));

				//create connection
				m_connection = std::make_unique<Connection<T>>(Connection<T>::owner::CLIENT, m_context,
						asio::ip::tcp::socket(m_context),m_QMessagesIn);

				m_connection->connectToServer(m_endpoints,this);


				thrContext = std::thread([this]() { m_context.run(); });

			} catch (std::exception& e){
				std::cerr << "Client Exception: " << e.what() << "\n";
				return false;
			}

			return true;
		}

		void disconnect(){
			//if we are still connected the disconnect
			if(isConnected()){
				m_connection->disconnect();
			}

			//regardless stop the context
			m_context.stop();
			//and join the thread
			if(thrContext.joinable()) { thrContext.join();}

			m_connection.release();
		}

		bool isConnected(){
			if(m_connection){
				return m_connection->isConnected();
			} else {
				return false;
			}
		}

		void send(const Message<T>& msg){
			if(isConnected()){
				m_connection->send(msg);
			}
		}

		TSQueue<OwnedMessage<T>>& incoming(){
			return m_QMessagesIn;
		}
	};
}

#endif //NET_CLIENT_H
