#pragma once

#include "Base/Renderer/RendererAPI.h"

namespace Workbench
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const uint32_t  width, const uint32_t height) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}