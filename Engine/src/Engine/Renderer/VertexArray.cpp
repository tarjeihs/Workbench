#include "wbpch.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Workbench
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPIType())
		{
			case RendererAPI::APIType::OpenGL: return new OpenGLVertexArray();
		}

		WB_ENGINE_ASSERT(false, "APIType is out of scope.");
		return nullptr;
	}
}