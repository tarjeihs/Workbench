#pragma once

#include <cstdint>

namespace Workbench
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
	protected:
		inline const uint32_t& GetRendererIDImpl() const { return m_RendererID; }
		inline void SetRendererIDImpl(uint32_t id) { m_RendererID = id; }
	private:
		uint32_t m_RendererID;
	};
}