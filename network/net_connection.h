#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "net_common.h"
#include "net_TSQueue.h"
#include "net_message.h"

//have a virtual function that checks if a message is correct that the user has to override
//the client sends the server a validation message and the server calls the function
//bool validateFunc(Message msg) { return false; }
//this can be used so a client must send the server a password to connect

namespace net
{
	//forward declare server
	template<typename T>
	class ServerInterface;

	//forward declare client
	template<typename T>
	class ClientInterface;

	template<typename T>
	class Connection : public std::enable_shared_from_this<Connection<T>>
	{
	public:
		enum class owner{ SERVER, CLIENT };
	private:
		//ASYNC
		void readHeader(){
			asio::async_read(m_socket, asio::buffer(&m_msgTemporaryIn.header, sizeof(MessageHeader<T>)),
				[this](std::error_code ec, std::size_t length){
					if(!ec){
						if(m_msgTemporaryIn.header.size > 0){
							m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
							readBody();
						} else {
							//if there is no body then we're done with this message
							addToIncomingMessageQueue();
						}
					} else {
						std::cout << "[" << id << "] Read Header Fail\n";
						m_socket.close();
					}
				}
			);
		}
		//ASYNC
		void readBody(){
			asio::async_read(m_socket,asio::buffer(m_msgTemporaryIn.body.data(),m_msgTemporaryIn.body.size()),
				[this](std::error_code ec, std::size_t length){
					if(!ec){
						addToIncomingMessageQueue();
					} else {
						std::cout << "[" << id << "] Read Body Fail\n";
						m_socket.close();
					}
				}
			);
		}

		//ASYNC
		void writeHeader(){
			asio::async_write(m_socket, asio::buffer(&m_qMessagesOut.front().header, sizeof(MessageHeader<T>)),
				[this](std::error_code ec, std::size_t length){
					if(!ec && !m_qMessagesOut.empty()){
						if(m_qMessagesOut.front().body.size() > 0){
							writeBody();
						} else {
							//if there isn't a body we're done with the message
							m_qMessagesOut.pop_front();

							//if we still have messages, process them
							if(!m_qMessagesOut.empty()){
								writeHeader();
							}
						}
					} else {
						std::cout << "[" << id << "] Write Header Fail\n";
						m_socket.close();
					}
				}
			);
		}
		//ASYNC
		void writeBody(){
			asio::async_write(m_socket, asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
				[this](std::error_code ec, std::size_t length){
					if(!ec && !m_qMessagesOut.empty()){
						m_qMessagesOut.pop_front();

						//if we still have messages, process them
						if(!m_qMessagesOut.empty()){
							writeHeader();
						}
					} else {
					  std::cout << "[" << id << "] Write Body Fail\n";
					  m_socket.close();
					}
				}
			);
		}

		void addToIncomingMessageQueue(){
			if(m_ownerType == owner::SERVER){
				m_qMessagesIn.push_back({this->shared_from_this(), m_msgTemporaryIn });
			} else {
				m_qMessagesIn.push_back({nullptr, m_msgTemporaryIn });
			}

			readHeader();
		}

		uint64_t scramble(uint64_t input){
			//return input;
			uint64_t out = input ^ 0xDEADBEEFC0DECAFE;
			out = (out & 0xF0F0F0F0F0F0F0) >> 4 | (out & 0x0F0F0F0F0F0F0F) << 4;
			return out ^ 0xC0DEFACE12345678;
		}

		void writeValidation(){
			asio::async_write(m_socket, asio::buffer(&m_handShakeOut,sizeof(uint64_t)),
				[this](std::error_code ec, std::size_t length){
					if(!ec){
						if(m_ownerType == owner::CLIENT){
							readHeader();
						}
					} else {
						m_socket.close();
					}
				}
			);
		}

		void readValidation(net::ServerInterface<T>* server = nullptr){
			asio::async_read(m_socket,asio::buffer(&m_handShakeIn, sizeof(uint64_t)),
				[this,server](std::error_code ec, std::size_t length){
					if(!ec){
						if(m_ownerType == owner::SERVER){
							if(m_handShakeIn == m_handShakeCheck){
								std::cout << "Client Validated\n";
								server->onClientValidated(this->shared_from_this());

								readHeader();
							} else {
								std::cout << "Client Disconnected (Fail Validation)\n";
								m_socket.close();
							}
						} else {
							m_handShakeOut = scramble(m_handShakeIn);

							writeValidation();
						}
					} else {
						std::cout << "Client disconnected (ReadValidation)\n";
						m_socket.close();
					}
				}
			);
		}

		//used for things like ver checking or passwords
		void writeClientCheck(net::ClientInterface<T>* client){
			Message<T> msg = client->sendClientCheck();

			asio::async_write(m_socket, asio::buffer(&msg.header, sizeof(MessageHeader<T>)),
				[this,msg](std::error_code ec, std::size_t length) {
					if (!ec) {
						if (msg.body.size() > 0) {
							//writeBody();
							asio::async_write(m_socket, asio::buffer(msg.body.data(), msg.body.size()),
								[this,msg](std::error_code ec, std::size_t length) {
									if (ec) {
										m_socket.close();
									}
								}
							);
						}
					} else {
						//std::cout << "(ClientCheck) Write Header Fail\n";
						m_socket.close();
					}
				}
			);

			//weather the client passes of fails depends on the server
			readHeader();
		}

		void readClientCheckHeader(net::ServerInterface<T>* server) {
			//read in a message
			asio::async_read(m_socket, asio::buffer(&m_clientCheckMsg.header, sizeof(MessageHeader<T>)),
				[this,server](std::error_code ec, std::size_t length) {
					if (!ec) {
						if (m_clientCheckMsg.header.size > 0) {
							m_clientCheckMsg.body.resize(m_clientCheckMsg.header.size);
							readClientCheckBody(server);
						} else if (!server->checkClient(m_clientCheckMsg)) {
							std::cout << "Client disconnected (ClientCheck Fail)\n";
							m_socket.close();
						} else {
							std::cout << "Client Validated\n";
							server->onClientValidated(this->shared_from_this());
							readHeader();
						}
					} else {
						std::cout << "Client disconnected (ClientCheck) read header fail\n";
						m_socket.close();
					}
				}
			);
		}

		void readClientCheckBody(net::ServerInterface<T>* server){
			//ReadBody
			asio::async_read(m_socket, asio::buffer(m_clientCheckMsg.body.data(), m_clientCheckMsg.body.size()),
				[this,server](std::error_code ec, std::size_t length) {
					if (!ec) {
						//TODO fix it so that the client check will get called if there is no message body
						//check the message to see if it passes
						if (!server->checkClient(m_clientCheckMsg)) {
							 std::cout << "Client disconnected (ClientCheck Fail)\n";
							 m_socket.close();
						} else {
							std::cout << "Client Validated\n";
							server->onClientValidated(this->shared_from_this());
							readHeader();
						}
					} else {
						std::cout << "Read header fail\n";
						std::cout
								<< "Client disconnected (ClientCheck) read header fail\n";
						m_socket.close();
					}
				}

			);
		}

		void readClientCheckProcessMessage(net::ServerInterface<T>* server){

		}
/*
		void readClientCheck(net::ServerInterface<T>* server){
			Message<T> msg;
			//TODO rewrite this into seperate functions so that read head call read body which then call the check
			//TODO as when this dosen't happen we have race conditions (I think)

			//read in a message
			asio::async_read(m_socket, asio::buffer(&msg.header, sizeof(MessageHeader<T>)),
				[this](std::error_code ec, std::size_t length){
					if(!ec){
						if(msg.header.size > 0){
							msg.body.resize(msg.header.size);
							//ReadBody
							asio::async_read(m_socket,asio::buffer(msg.body.data(),msg.body.size()),
								[this](std::error_code ec, std::size_t length) {
									if (!ec) {
										//check the message to see if it passes
										if(!server->checkClient(msg)){
											std::cout << "Client disconnected (ClientCheck Fail)\n";
											m_socket.close();
										} else {
											std::cout << "Client Validated\n";
											server->onClientValidated(this->shared_from_this());
											readHeader();
										}
									} else {
										std::cout << "Read header fail\n";
										std::cout << "Client disconnected (ClientCheck) read header fail\n";
										m_socket.close();
									}
								}
							);
						}
					} else {
						std::cout << "Client disconnected (ClientCheck) read header fail\n";
						m_socket.close();
					}
				}
			);
		}*/
	protected:
		asio::ip::tcp::socket m_socket;
		asio::io_context& m_asioContext;

		//stores the outgoing messages
		TSQueue<Message<T>> m_qMessagesOut;
		//stores incoming messages
		TSQueue<OwnedMessage<T>>& m_qMessagesIn;
		Message<T> m_msgTemporaryIn;

		owner m_ownerType = owner::SERVER;
		uint32_t id = 0;

		uint64_t m_handShakeOut = 0;
		uint64_t m_handShakeIn = 0;
		uint64_t m_handShakeCheck = 0;

		Message<T> m_clientCheckMsg;
	public:
		Connection(owner parent, asio::io_context& asioContext,asio::ip::tcp::socket socket, TSQueue<OwnedMessage<T>>& qIn)
			: m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
		{
			m_ownerType = parent;

			if(m_ownerType == owner::SERVER) {
				//generate the handshake
				//scramble the handshake
				m_handShakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

				m_handShakeCheck = scramble(m_handShakeOut);
			} else {
				m_handShakeIn = 0;
				m_handShakeOut = 0;
				//default the handshake vals
			}
		}

		virtual ~Connection() {}

		void connectToClient(net::ServerInterface<T>* server, uint32_t uid = 0){
			if(m_ownerType == owner::SERVER){
				if(m_socket.is_open()){
					id = uid;

					readClientCheckHeader(server);

					//writeValidation();
					//readValidation(server);

					//readHeader();
				}
			}
		}

		void connectToServer(const asio::ip::tcp::resolver::results_type& endpoints, net::ClientInterface<T>* client){
			if(m_ownerType == owner::CLIENT){
				asio::async_connect(m_socket, endpoints,
					[this,client](std::error_code ec, asio::ip::tcp::endpoint endpoint){
						if(!ec){
							writeClientCheck(client);

							//readValidation();
							//readHeader();
						} else {
							disconnect();
						}
					}
				);
			}
		}

		void disconnect(){
			if(isConnected()){
				asio::post(m_asioContext, [this]() { m_socket.close(); });
			}
		}

		bool isConnected() const {
			return m_socket.is_open();
		}

		void send(const Message<T>& msg){
			asio::post(m_asioContext,
				[this, msg](){
					bool writingMessage = !m_qMessagesOut.empty();
					m_qMessagesOut.push_back(msg);
					//if asio isn't in the write message loop put it in it
					if(!writingMessage) { writeHeader(); }
				}
			);
		}

		uint32_t getID() const { return id; }
	};
}

#endif //NET_CONNECTION_H
