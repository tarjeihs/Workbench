#include "wbpch.h"
#include "Engine/Renderer/Buffer.h"

#include "Engine/Renderer/Renderer.h" 
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Workbench
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		WB_ENGINE_ASSERT(false, "Failed to specify current RendererAPI.");
		return nullptr;
	}	
	
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		WB_ENGINE_ASSERT(false, "Failed to specify current RendererAPI.");
		return nullptr;
	}
}