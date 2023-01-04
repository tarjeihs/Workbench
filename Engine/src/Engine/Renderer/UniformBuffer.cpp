#include "wbpch.h"
#include "UniformBuffer.h"

#include "Engine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Workbench
{
	std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLUniformBuffer>(size, binding);
		}

		WB_ENGINE_ASSERT(false, "APIType is out of scope.");
	}
}