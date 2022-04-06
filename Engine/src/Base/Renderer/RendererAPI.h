#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Workbench
{
	class RendererAPI
	{
	public:
		enum class APIType
		{
			None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3
		};
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	
		inline static APIType GetAPIType() { return s_APIType; }
	protected:
		static APIType s_APIType;
	};
}