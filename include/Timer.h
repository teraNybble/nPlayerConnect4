#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace Game2D
{
	class Timer
	{
	private:
		using time_point = std::chrono::high_resolution_clock::time_point;
		using high_resolution_clock = std::chrono::high_resolution_clock;

		time_point startTime;
	public:
		using seconds = std::chrono::seconds;
		using miliseconds = std::chrono::milliseconds;

		//timer is automatically started when it is crated
		Timer()
		{ startTime = high_resolution_clock::now(); }

		template<typename _ToDur>
		int elapsedTime() const
		{
			auto elapsedTime = high_resolution_clock::now() - startTime;

			return std::chrono::duration_cast<_ToDur>(elapsedTime).count();
		}
	};
}

#endif //TIMER_H