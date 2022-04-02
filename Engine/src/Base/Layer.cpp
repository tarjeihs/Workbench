#include "wbpch.h"
#include "Layer.h"

namespace Workbench
{
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{
	}
}