#pragma once

#include "Base/Layer.h"

namespace Workbench
{
	class WORKBENCH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender(Timestep ts) override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0;
	};
}