#pragma once

#include "Core.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Timestep.h"

namespace Workbench
{
	class WORKBENCH_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} // Create
		virtual void OnDetach() {} // Destroy
		virtual void OnUpdate(Timestep ts) {} // Layer Update
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}