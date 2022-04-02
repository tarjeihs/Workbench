#pragma once

#include "Base/Layer.h"

namespace Workbench
{
	class WORKBENCH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnWindowCloseEvent(WindowCloseEvent& event);

		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypeEvent(KeyTypeEvent& event);

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseButtonMoveEvent(MouseMoveEvent& event);
		bool OnMouseButtonScrollEvent(MouseScrollEvent& event);

		float m_Time = 0.0;
	};
}