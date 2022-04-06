#include "wbpch.h"
#include "Buffer.h"

#include "Renderer.h" 
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Workbench
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		WB_ENGINE_ASSERT(false, "Failed to specify current RendererAPI.");
	}	
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		WB_ENGINE_ASSERT(false, "Failed to specify current RendererAPI.");
	}
}