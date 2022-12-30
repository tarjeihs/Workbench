#pragma once

#include "Workbench.h"

class EditorLayer : public Workbench::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Workbench::Timestep ts) override;
	virtual void OnImGuiRender(Workbench::Timestep ts) override;
	virtual void OnEvent(Workbench::Event& event) override;
};