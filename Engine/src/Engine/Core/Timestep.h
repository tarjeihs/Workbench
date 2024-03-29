#pragma once

namespace Workbench
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		float GetMilliseconds() const { return m_Time * 1000.0f; }
		float GetSeconds() const { return m_Time; }

		inline operator float() const { return m_Time; }
	private:
		float m_Time;
	};
}