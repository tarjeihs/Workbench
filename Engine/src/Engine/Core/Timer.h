#pragma once

#include <chrono>

namespace Workbench
{
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		Timer(Timer&) = delete;
		Timer(Timer&&) = delete;

		inline void Timer::Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		inline float Elapsed() const
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_Start)
				.count() * 0.001 * 0.001 * 0.001;
		}

		inline float ElapsedMilliseconds() const
		{
			return Elapsed() * 1000.0f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}