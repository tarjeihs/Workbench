#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Workbench
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void Shutdown()
		{
			s_RendererAPI->Shutdown();
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{ 
			s_RendererAPI->SetClearColor(color); 
		}

		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t  width, const uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) 
		{ 
			s_RendererAPI->DrawIndexed(vertexArray); 
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}