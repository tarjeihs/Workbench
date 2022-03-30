#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Workbench
{
	class WORKBENCH_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} // Create
		virtual void OnDetach() {} // Destroy
		virtual void OnUpdate() {} // Layer Update
		virtual void OnEvent(Event& event) {}

		inline const std::string GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}