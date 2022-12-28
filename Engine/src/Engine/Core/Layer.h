#pragma once

#include "Engine/Core/Base.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

#include "Timestep.h"

namespace Workbench
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} // Create
		virtual void OnDetach() {} // Destroy
		virtual void OnUpdate(Timestep ts) {} // Layer Update
		virtual void OnImGuiRender(Timestep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}