#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H

#include "net_common.h"

namespace net
{
	template <typename T>
	struct MessageHeader
	{
		T id{};
		uint32_t size = 0;
	};

	template <typename T>
	struct Message
	{
		MessageHeader<T> header{};
		std::vector<uint8_t> body;

		size_t size() const
		{
			return body.size();
			//return sizeof(MessageHeader<T>) + body.size();
		}

		//overload the output operator
		friend std::ostream& operator<< (std::ostream& os, const Message<T>& msg)
		{
			return os << "ID:" << int(msg.header.id) << "\tSize:" << msg.header.size;
		}

		//allow data to be inserted via << operator
		template<typename DataType>
		friend Message<T>& operator<< (Message<T>& msg, const DataType& data)
		{
			//make sure the data is simple enough to push
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to push");

			size_t i = msg.body.size();

			//allocate more space to the Message body
			msg.body.resize(msg.body.size() + sizeof(DataType));

			//move the data into the Message body
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

			//update the size of the Message in the Message header
			msg.header.size = msg.size();

			return msg; //allows the Message to be chained
		}

		//allow data to be taken from the Message (this treats the Message like a stack)
		template<typename DataType>
		friend Message<T>& operator>> (Message<T>& msg, DataType& data)
		{
			//make sure the data is simple enough to pop
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to pop");

			size_t i = msg.body.size() - sizeof(DataType);

			//take data from the Message
			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

			//reduce the size of the Message
			msg.body.resize(i);

			//update the size of the Message in the Message header
			msg.header.size = msg.size();

			return msg;//allows Message to be chained
		}
	};

	//forward declare the Connection
	template<typename T>
	class Connection;

	template<typename T>
	struct OwnedMessage
	{
		std::shared_ptr<Connection<T>> remote = nullptr;
		Message<T> msg;

		friend std::ostream& operator<< (std::ostream& os, const OwnedMessage<T>& msg){
			return os << msg.msg;
		}
	};
}

#endif //NET_MESSAGE_H