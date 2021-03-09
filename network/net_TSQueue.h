#ifndef NET_TSQUEUE_H
#define NET_TSQUEUE_H

#include "net_common.h"
#include "net_message.h"

#ifndef _WIN32
//windows isn't defining __cplusplus the same way linux does, so fuck checking it
#if __cplusplus < 201703L
#error This lib needs C++17 or greater
#endif
#endif // !_WIN32

namespace net
{
	template<typename T>
	class TSQueue
	{
	private:
	protected:
		std::mutex muxQueue;
		std::deque<T> deqQueue;
		std::condition_variable cvBlocking;
		std::mutex muxBlocking;
	public:
		TSQueue() = default;
		TSQueue(const TSQueue<T>&) = delete;

		virtual ~TSQueue() { clear(); }

		const T& front(){
			std::scoped_lock lock(muxQueue);
			return deqQueue.front();
		}

		const T& back(){
			std::scoped_lock lock(muxQueue);
			return deqQueue.back();
		}

		void push_back(const T& item){
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_back(std::move(item));

			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}

		void push_front(const T& item){
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_front(std::move(item));

			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}

		bool empty(){
			std::scoped_lock lock(muxQueue);
			return deqQueue.empty();
		}

		size_t count()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.size();
		}

		void clear(){
			std::scoped_lock lock(muxQueue);
			deqQueue.clear();
		}

		void wait()	{
			while(empty()){
				std::unique_lock<std::mutex> ul(muxBlocking);
				cvBlocking.wait(ul);
			}
		}

		T pop_front(){
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.front());
			deqQueue.pop_front();
			return t;
		}

		T pop_back(){
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.back());
			deqQueue.pop_back();
			return t;
		}
	};
}

#endif //NET_TSQUEUE_H